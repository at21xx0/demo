#include "node_api.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>
#include <time.h>

#ifdef ENABLE_SLEEP
#ifdef WIN32
#include <windows.h>
#define msleep(ms) Sleep(ms)
#else
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#ifndef ENABLE_SEM
#define ENABLE_SEM
#endif

#define msleep(ms) usleep(ms * 1000);
#if 0 
#include <sys/time.h>
long getMsec()
{
        long msec = 0;
        struct timeval t;

        gettimeofday(&t, NULL);
	msec = t.tv_sec * 1000 + (long)(t.tv_usec / 1000);
	return msec;
}
#endif 
#endif
#else
#define msleep(ms)
#endif

#if INT32_MAX == INTPTR_MAX
// #error "32"
#endif




void catch_f(napi_env env, napi_status status, char* file, int line) {
	napi_extended_error_info* e;
	if(status != napi_ok) {
		napi_get_last_error_info(env, (void *)&e);
		fprintf(stderr, "%s:%d %s\n", file, line, e->error_message);
		abort();
	}
}
#define CHECK(env, r) catch_f(env, r, __FILE__, __LINE__)


static napi_value Method(napi_env env, const napi_callback_info info) {
	napi_status status;
	napi_value value;
	status = napi_create_string_utf8(env, "[str]", NAPI_AUTO_LENGTH, &value);
	assert(status == napi_ok);
	return value;
}

static napi_value testType(napi_env env, const napi_callback_info info) {
#define F_TYPE_ERR "testType(Number, Number, callback)"
	napi_status status;
	napi_value value;
	napi_value jsthis;
	napi_value args[6];
	napi_valuetype t0;
	napi_valuetype t1;
	napi_valuetype t2;
	napi_valuetype t3;
	napi_valuetype t4;
	double i;
	double j;
	size_t argc = 6;

	napi_value cb;
	napi_value argv[10];
	napi_value global;
	napi_value result;

	napi_value fn;

	napi_value obj;

	bool b;

	char buf[1024];
	char *m;
	size_t size;
	size_t bz = 1024;

	napi_handle_scope scope;
	napi_value *pargv;
	napi_value v2;
	napi_value v3;
	int32_t index;
	uint32_t len;

	status = napi_get_cb_info(env, info, &argc, args, &jsthis, NULL);
	assert(status == napi_ok);
	if(argc != 6) {
		napi_throw_type_error(env, NULL, F_TYPE_ERR);
		return NULL;
	}
	status = napi_typeof(env, args[0], &t0);
	assert(status == napi_ok);
	status = napi_typeof(env, args[1], &t1);
	assert(status == napi_ok);
	status = napi_typeof(env, args[2], &t2);
	assert(status == napi_ok);
	status = napi_typeof(env, args[3], &t3);
	assert(status == napi_ok);
	status = napi_typeof(env, args[4], &t4);
	assert(status == napi_ok);
	if(t0 != napi_number || t1 != napi_number || t2 != napi_boolean || t3 != napi_function || t4 != napi_string)
	{
		napi_throw_type_error(env, NULL, F_TYPE_ERR);
		return NULL;
	}

	status = napi_get_value_double(env, args[0], &i);
	assert(status == napi_ok);
	status = napi_get_value_double(env, args[1], &j);
	assert(status == napi_ok);
	status = napi_create_double(env, i + j, &value);
	assert(status == napi_ok);

	cb = args[3];
	// status = napi_create_string_utf8(env, "test", NAPI_AUTO_LENGTH, argv);
	// assert(status == napi_ok);
	argv[0] = value;

	status = napi_get_global(env, &global);
	assert(status == napi_ok);
	status = napi_call_function(env, global, cb, 1, argv, &result);
	assert(status == napi_ok);

	status = napi_create_function(env, "test", NAPI_AUTO_LENGTH, &Method, NULL, &fn);
	assert(status == napi_ok);

	status = napi_create_object(env, &obj);
	assert(status == napi_ok);
	status = napi_set_named_property(env, obj, "arg0", args[0]);
	assert(status == napi_ok);
	status = napi_has_named_property(env, obj, "arg0", &b);
	assert(status == napi_ok);
	assert(b != 0);
	status = napi_set_named_property(env, obj, "arg0_add_arg1", value);
	assert(status == napi_ok);
	status = napi_set_named_property(env, obj, "callback_result", result);
	assert(status == napi_ok);
	status = napi_set_named_property(env, obj, "fn", fn);
	assert(status == napi_ok);
	status = napi_set_property(env, obj, value, result); // obj[value] = result;
	assert(status == napi_ok);
	// napi_get_property napi_has_property napi_delete_property(env, obj, key, &b);

	status = napi_get_value_bool(env, args[2], &b);
	assert(status == napi_ok);

	b = 1 ^ b;
	napi_get_boolean(env, b, &value);

	status = napi_set_named_property(env, obj, "bool", value);
	assert(status == napi_ok);

	m = buf;
	*m = '[';
	*(++m) = '\0';
	bz -= 1;
	status = napi_get_value_string_utf8(env, args[4], m, bz, &size);
	assert(status == napi_ok);
	assert(size != 0);
	bz -= size + 1;
	m += size;
	*m = ']';
	*(++m) = '\0';
	status = napi_create_string_utf8(env, buf, NAPI_AUTO_LENGTH, &value);
	assert(status == napi_ok);

	status = napi_set_named_property(env, obj, "str", value);
	assert(status == napi_ok);

	status = napi_is_array(env, args[5], &b);
	assert(status == napi_ok);
	(void)len;
	if(!b)
		(void)0;
	else if(napi_get_named_property(env, global, "console", &v2) == napi_ok && napi_get_named_property(env, v2, "log", &v3) == napi_ok)
	{
		status = napi_get_array_length(env, args[5], &len);
		assert(status == napi_ok);
		argc = len;
		pargv = (napi_value *)malloc(len * sizeof(napi_value));
		assert(pargv != NULL);
		status = napi_open_handle_scope(env, &scope);
		assert(pargv != NULL);
		for(index = 0;index < (int32_t)len;++index)
		{
			// napi_has_element(env, args[5], index, &b); // b == 1
			status = napi_get_element(env, args[5], index, pargv + index);
			assert(status == napi_ok);
		}
		status = napi_call_function(env, v2, v3, argc, pargv, &result); // console.log.apply(console, argv[5]
		assert(status == napi_ok);
		status = napi_close_handle_scope(env, scope); // free pargv[0] pargv[1] ...
		assert(status == napi_ok);
		free((void *)pargv);
	}

	status = napi_create_array(env, &value);
       	// napi_status napi_create_array_with_length(napi_env env, size_t length, napi_value* result) assert(status == napi_ok);
	for(index = 0;index != 5;++index)
	{
		status = napi_create_int32(env, index, &v2);
		// int32 int64 uint32 double
		assert(status == napi_ok);
		status = napi_set_element(env, value, index, v2);
		assert(status == napi_ok);
	}

	status = napi_set_named_property(env, obj, "arr", value);
	assert(status == napi_ok);

	return obj;
}

typedef struct async_t{
	napi_async_work work;
	bool b;
	napi_deferred deferred;
	napi_ref callback;
	napi_threadsafe_function tsfn;
}async_t;

void async_callJs(napi_env env, napi_value cb, void* context, void* data) { // threadsafe_function
	napi_value result;
	napi_value global;
	napi_status status;
	napi_value argv[2];
	(void)context;
	if(env != NULL) {
		status = napi_get_boolean(env, *(bool *)data, &argv[0]);
		assert(status == napi_ok);
		status = napi_get_undefined(env, &argv[1]);
		assert(status == napi_ok);
		status = napi_get_global(env, &global);
		assert(status == napi_ok);
		status = napi_call_function(env, global, cb, 2, argv, &result);
		assert(status == napi_ok);
	}
	free(data);
}

void async_execute(napi_env env, void *data) {
	bool *data2;
	async_t* p = (async_t *)data;
	napi_status status;
	(void)env;
	// NAPI_EXTERN napi_status
	// napi_get_threadsafe_function_context(napi_threadsafe_function func, void** result);
	// 
	// execute_thread
	msleep(1000);
	// printf("async_execute_bool: %d\n", ((async_t *)data)->b);
	// do something
	// (async_t *)data->b ^= 1;
	if(p->tsfn) {
		// safe
		// call threadsafe_function
		status = napi_acquire_threadsafe_function(p->tsfn);
		assert(status == napi_ok);
		data2 = (bool *)malloc(sizeof(bool));
		assert(data2 != NULL);
		*data2 = p->b;
		status = napi_call_threadsafe_function(p->tsfn, (void *)data2, napi_tsfn_blocking); // napi_tsfn_blocking return napi_ok // napi_tsfn_noblocking return napi_ok or napi_queue_full
		assert(status == napi_ok);
		status = napi_release_threadsafe_function(p->tsfn, napi_tsfn_release);
		assert(status == napi_ok);
	}
} 

void async_complete(napi_env env, napi_status status0, void *data) {
	async_t *p = (async_t *)data;
	napi_value value;
	napi_value err;
	napi_value argv[2];
	napi_value message;
	napi_value callback;
	napi_value global;
	napi_status status;

	if(p->b) {
		status = napi_get_undefined(env, &err);
		assert(status == napi_ok);
	} else  {
		status = napi_create_string_utf8(env, "testAsync_error", NAPI_AUTO_LENGTH, &value);
		assert(status == napi_ok);
		status = napi_create_string_utf8(env, "testError", NAPI_AUTO_LENGTH, &message);
		assert(status == napi_ok);
		status = napi_create_error(env, value, message, &err); // env, code, msg, result
		assert(status == napi_ok);
	}
	status = napi_get_boolean(env, p->b, &value);
	assert(status == napi_ok);
	if(p->tsfn) {
		status = napi_release_threadsafe_function(p->tsfn, napi_tsfn_release);
		assert(status == napi_ok);
	} else if(p->callback) {
                napi_get_reference_value(env, p->callback, &callback);
		argv[0] = value;
		argv[1] = err;
		status = napi_get_global(env, &global);
		assert(status == napi_ok);
		status = napi_call_function(env, global, callback, 2, argv, &value);
		assert(status == napi_ok);
                status = napi_delete_reference(env, p->callback);
		assert(status == napi_ok);
	} else if(p->b)
		status = napi_resolve_deferred(env, p->deferred, value);
	else
		status = napi_reject_deferred(env, p->deferred, err);
	assert(status == napi_ok);

	status = napi_delete_async_work(env, p->work);
	assert(status == napi_ok);
	free((void *)p);
}


napi_value async_testAsync(napi_env env, const napi_callback_info info) {
#define TEST_PROMISE_TYPE_ERROR "[boolean, ]callback"
	napi_status status;
	size_t argc = 2;
	napi_value args[2];
	napi_valuetype t0;
	async_t *p;
	napi_value promise;
	napi_value resource_name;
	status = napi_get_cb_info(env, info, &argc, args, NULL, NULL);
	assert(status == napi_ok);
	status = napi_typeof(env, args[0], &t0);
	if(argc == 0)
	{
		napi_throw_type_error(env, NULL, TEST_PROMISE_TYPE_ERROR);
		return NULL;
	}
	assert(status == napi_ok);
	if(t0 != napi_boolean && t0 != napi_function)
	{
		napi_throw_type_error(env, NULL, TEST_PROMISE_TYPE_ERROR);
		return NULL;
	}
	p = (async_t *)malloc(sizeof(async_t));
	assert(p != NULL);
	memset(p, '\0', sizeof(async_t));
	status = napi_create_string_utf8(env, "testAsync", NAPI_AUTO_LENGTH, &resource_name);
	assert(status == napi_ok);
	if(t0 == napi_function) {
		p->b = 1;
		status = napi_create_threadsafe_function(env, args[0], NULL, resource_name, 0 /* max_queue_size 0 unlimted */, 1 /* initial_thread_count */, NULL /* void* thread_finalize_data */, NULL /* thread_finlize_cb */, NULL /* void* context */, &async_callJs, &(p->tsfn));
		assert(status == napi_ok);
		status = napi_get_undefined(env, &promise);
		assert(status == napi_ok);
	} else {
		status = napi_get_value_bool(env, args[0], &p->b);
		assert(status == napi_ok);
		
		if(argc == 2) {
			status = napi_typeof(env, args[1], &t0);
			if(t0 != napi_function) {
				free((void *)p);
				napi_throw_type_error(env, NULL, TEST_PROMISE_TYPE_ERROR);
				return NULL;
			}
			status = napi_create_reference(env, args[1], 1, &p->callback); // env, obj, ref_count, ref
			assert(status == napi_ok);
			// napi_reference_ref(env, &p->callback, &len); // reference_count+1 
			// NAPI_EXTERN napi_status napi_reference_unref(napi_env env, napi_ref ref, uint32_t* result);
			// napi_get_reference_value napi_delete_reference
			status = napi_get_undefined(env, &promise);
			assert(status == napi_ok);
		} else {
			status = napi_create_promise(env, &p->deferred, &promise);
			assert(status == napi_ok);
			// napi_status napi_is_promise(napi_env env, napi_value value, bool* is_promise);
		}
	}
	status = napi_create_async_work(env, NULL, resource_name, &async_execute, &async_complete, (void *)p, &p->work);
	assert(status == napi_ok);
	status = napi_queue_async_work(env, p->work);
	assert(status == napi_ok);
	return promise;
}


napi_value test_nVersion(napi_env env, const napi_callback_info info) {
	napi_value value;
	napi_value obj;
	napi_node_version* v;
	uint32_t t;
	// status = napi_get_cb_info(env, info, NULL, NULL, &jsthis, NULL);
	CHECK(env, napi_get_node_version(env, (void *)&v)); // warning
	CHECK(env, napi_create_object(env, &obj));
	CHECK(env, napi_create_int32(env, v->major, &value));
	CHECK(env, napi_set_named_property(env, obj, "major", value));
	CHECK(env, napi_create_int32(env, v->minor, &value));
	CHECK(env, napi_set_named_property(env, obj, "minor", value));
	CHECK(env, napi_create_int32(env, v->patch, &value));
	CHECK(env, napi_set_named_property(env, obj, "patch", value));
	CHECK(env, napi_create_string_utf8(env, v->release, NAPI_AUTO_LENGTH, &value));
	CHECK(env, napi_set_named_property(env, obj, "release", value));
	CHECK(env, napi_get_version(env, &t));
	CHECK(env, napi_create_int32(env, t, &value));
	CHECK(env, napi_set_named_property(env, obj, "version", value));
	return obj;
}



typedef struct f_buf{
	int size;
	int n;
	char data[0];
}f_buf;

typedef struct f_t{
	napi_async_work work;
	napi_threadsafe_function data;
	napi_ref end;
	// pthread_mutex_t mutex;
#ifdef ENABLE_SEM
	sem_t sem;
#endif
	int status;
	int limit_n;
	int n;
	int js_n;
	f_buf **list;
	int list_start;
	int list_end;
	int list_len;
	int resume_n;
	int bufsize;
	char fn[0];
}f_t;
// sizeof(int) == sizeof(f_buf)

#define F_STATUS_DEFAULT 0
#define F_STATUS_PAUSE 1
#define F_STATUS_RESUME 2
#define F_STATUS_ERROR 3

void f_external_buffer_free(napi_env env, void *data, void *hint) {
	(void)env;
	(void)hint;
	free(data - sizeof(f_buf));
}
napi_value f_pause(napi_env env, const napi_callback_info info) {
	napi_status status;
	napi_value undefined;
	f_t* p;
	status = napi_get_cb_info(env, info, NULL, NULL, NULL, (void **)&p);
	assert(status == napi_ok);
	status = napi_get_undefined(env, &undefined);
	assert(status == napi_ok);
	p->status = F_STATUS_PAUSE;
	return undefined;
}
napi_value f_resume(napi_env env, const napi_callback_info info) {
	napi_status status;
	napi_value undefined;
	f_t* p;
	status = napi_get_cb_info(env, info, NULL, NULL, NULL, (void **)&p);
	assert(status == napi_ok);
	status = napi_get_undefined(env, &undefined);
	assert(status == napi_ok);
	p->status = F_STATUS_RESUME;
	p->resume_n = 1;
#ifdef ENABLE_SEM
	sem_post(&p->sem);
#endif

	return undefined;
}
void f_data_callJs(napi_env env, napi_value cb, void* context, void* data) { // threadsafe_function
#define F_BUF_LIST_EXTRA_SIZE 64
	napi_value exBuffer;
	napi_value result;
	napi_value global;
	napi_status status;
	int n;
	int i;
	int len;
	f_buf* buf = (f_buf*)data;
	f_t* p = (f_t*)context;
	if(env == NULL)
	{
		if(data)
			free(data);
		return;
	}
	status = napi_get_global(env, &global);
	assert(status == napi_ok);
	do{
		if(data == NULL) {
			if(p->status == F_STATUS_PAUSE || p->list_start == p->list_end) {
				if(p->status != F_STATUS_PAUSE)
				{
					p->status = F_STATUS_DEFAULT;
				}
				break;
			}
			buf = p->list[p->list_start];
			++p->list_start;
		} else if(p->status != F_STATUS_DEFAULT || p->list_start != p->list_end) {
			len = (p->n - buf->n) + 1;
			// for(i = 0;i < 100;++i);
			if(p->list_len - p->list_end + p->list_start < len)
			{
				len = len + F_BUF_LIST_EXTRA_SIZE;
				p->list_len = len;
			}
			else if(p->list_len - p->list_end < len) {
				for(i = 0, n = p->list_start, len = p->list_end;n != len;++i, ++n)
					p->list[i] = p->list[n];
				p->list_start = 0;
				p->list_end = i;
				if(len - i > F_BUF_LIST_EXTRA_SIZE * 2) {
					p->list_len -= F_BUF_LIST_EXTRA_SIZE;
					len = p->list_len;
				} else
					len = 0;
			} else
				len = 0;
			if(len != 0)
				p->list = (f_buf **)realloc((void *)p->list, sizeof(f_buf) * len);
			assert(p->list != NULL);
			p->list[p->list_end] = buf;
			++p->list_end;
			if(p->status == F_STATUS_DEFAULT)
			{
				data = NULL;
				continue;
			}
			break;
		}
		p->js_n = buf->n;
		status = napi_create_external_buffer(env, buf->size, buf->data, f_external_buffer_free, NULL, &exBuffer);
		assert(status == napi_ok);
		// buf->size = 0;
		status = napi_call_function(env, global, cb, 1, &exBuffer, &result);
		assert(status == napi_ok); // napi_pending_exception
#ifdef ENABLE_SEM
		sem_post(&p->sem);
#endif
	} while(data == NULL);
#ifdef ENABLE_SEM
		sem_post(&p->sem);
#endif
}
void f_execute(napi_env env, void *data) {
	f_t* p = (f_t *)data;
	f_buf *buf = NULL;
	FILE *foo;
	int fEnd = 0;
	int i;
	int n;
	// size_t size;
	napi_status status;

	status = napi_acquire_threadsafe_function(p->data);
	assert(status == napi_ok);
	foo = fopen(p->fn, "r");
	if(foo == NULL)
	{
		p->status = F_STATUS_ERROR;
		return;
	}
#ifdef ENABLE_SEM
	sem_init(&p->sem, 0, 0);
#endif
	while(1) {
		if(fEnd && p->n == p->js_n)
			break;
		else if(!fEnd && ((p->limit_n == 0) || p->n - p->js_n < p->limit_n)) // status == F_STATUS_PAUSE
			(void)0;
		else {
			if(p->resume_n != 0) {
				p->resume_n = 0;
				status = napi_call_threadsafe_function(p->data, NULL, napi_tsfn_blocking);
				assert(status == napi_ok);
			}
#ifdef ENABLE_SEM
			sem_wait(&p->sem);
#else
			msleep(1);
#endif
			continue;
		}
		buf = (f_buf*)malloc(sizeof(f_buf) + p->bufsize);
		assert(buf != NULL);
		buf->size = fread(buf->data, 1, p->bufsize, foo);
		buf->n = ++p->n;
		status = napi_call_threadsafe_function(p->data, (void *)buf, napi_tsfn_blocking);
		assert(status == napi_ok);
		fEnd = feof(foo);
	}
	fclose(foo);
#ifdef ENABLE_SEM
	sem_destroy(&p->sem);
#endif

	status = napi_release_threadsafe_function(p->data, napi_tsfn_release);
	assert(status == napi_ok);
}

void f_complete(napi_env env, napi_status status0, void *data) {
	napi_status status;
	napi_value global;
	napi_value end;
	napi_value result;
	f_t *p = (f_t *)data;

	status = napi_get_reference_value(env, p->end, &end);
	assert(status == napi_ok);
	status = napi_get_global(env, &global);
	assert(status == napi_ok);
	status = napi_call_function(env, global, end, 0, NULL, &result);
	assert(status == napi_ok);
	status = napi_delete_reference(env, p->end);
	assert(status == napi_ok);

	status = napi_release_threadsafe_function(p->data, napi_tsfn_release);
	assert(status == napi_ok);
	status = napi_delete_async_work(env, p->work);
	assert(status == napi_ok);
	if(p->status == F_STATUS_ERROR) {
		napi_throw_error(env, NULL, "No such File");
	}
	// pthread_mutex_destroy(&p->mutex);
	if(p->list)
		free((void *)p->list);

	free((void *)p);
}
napi_value f_testLoadFile(napi_env env, const napi_callback_info info) {
#define F_TYPE_LOADFILE_ERR "file_full_path, data(buffer), end(), boolean_enable_pause"
#define F_BUFFER_BUFSIZE 1024 * 32
#define F_LIMIT_N 8 /* 8 * BUFSIZE*/
#define F_TYPE_LOAD_BUFSIZE 1024
	char buf[F_TYPE_LOAD_BUFSIZE];
	napi_value value;
	napi_value obj;
	napi_value resource_name;
	napi_value argv[4];
	size_t argc = 4;
	napi_valuetype t0;
	napi_valuetype t1;
	napi_valuetype t2;
	size_t size;
	f_t* p;
	napi_status status;
	bool b;
	
	status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
	if(argc < 3) {
		napi_throw_type_error(env, NULL, F_TYPE_LOADFILE_ERR);
		return NULL;
	}
	status = napi_typeof(env, argv[0], &t0);
	assert(status == napi_ok);
	status = napi_typeof(env, argv[1], &t1);
	assert(status == napi_ok);
	status = napi_typeof(env, argv[2], &t2);
	assert(status == napi_ok);
	if(t0 != napi_string || t1 != napi_function || t2 != napi_function) {
		napi_throw_type_error(env, NULL, F_TYPE_LOADFILE_ERR);
		return NULL;
	}
	status = napi_get_value_string_utf8(env, argv[0], buf, F_BUFFER_BUFSIZE, &size);
	assert(status == napi_ok);
	p = (f_t *)malloc(sizeof(f_t) + size + 1);
	assert(p != NULL);
	memset((void *)p, '\0', sizeof(f_t));
	strcpy(p->fn, buf);
	p->bufsize = F_BUFFER_BUFSIZE;
	p->limit_n = F_LIMIT_N;
	// pthread_mutex_init(&p->mutex, NULL);

	status = napi_create_string_utf8(env, "testLoadFile", NAPI_AUTO_LENGTH, &resource_name);
	assert(status == napi_ok);
	status = napi_create_threadsafe_function(env, argv[1], NULL, resource_name, 0, 1, NULL, NULL, (void *)p, &f_data_callJs, &(p->data));
	assert(status == napi_ok);

	status = napi_create_reference(env, argv[2], 1, &p->end);
	assert(status == napi_ok);


	b = 0;
	if(argc == 4) {
		status = napi_typeof(env, argv[3], &t0);
		assert(status == napi_ok);
		if(t0 == napi_boolean) {
			status = napi_get_value_bool(env, argv[3], &b);
			assert(status == napi_ok);
		}
	}
	if(!b) {
		status = napi_get_undefined(env, &obj);
		assert(status == napi_ok);
		return obj;
	}
	status = napi_create_object(env, &obj);
	assert(status == napi_ok);

	status = napi_create_function(env, NULL, 0, &f_pause, (void *)p, &value);
	assert(status == napi_ok);
	status = napi_set_named_property(env, obj, "pause", value);
	assert(status == napi_ok);

	status = napi_create_function(env, NULL, 0, &f_resume, (void *)p, &value);
	assert(status == napi_ok);
	status = napi_set_named_property(env, obj, "resume", value);
	assert(status == napi_ok);

	status = napi_create_async_work(env, NULL, resource_name, &f_execute, &f_complete, (void *)p, &p->work);
	assert(status == napi_ok);
	status = napi_queue_async_work(env, p->work);
	assert(status == napi_ok);
	return obj;
}

napi_value test_copyBuffer(napi_env env, const napi_callback_info info) {
	napi_status status;
	napi_value buffer;
	napi_value buffer2;
	void* data;
	void* data2;
	size_t argc = 1;
	size_t len;
	bool b;
	status = napi_get_cb_info(env, info, &argc, &buffer, NULL, NULL);
	assert(status == napi_ok);
	status = napi_is_buffer(env, buffer, &b);
	assert(status == napi_ok);
	if(b) {
		status = napi_get_buffer_info(env, buffer, &data, &len);
		assert(status == napi_ok);
	} else {
		status = napi_is_arraybuffer(env, buffer, &b);
		assert(status == napi_ok);
		if(b) {
			status = napi_get_arraybuffer_info(env, buffer, &data, &len);
			assert(status == napi_ok);
		} else {
			napi_throw_type_error(env, NULL, "buffer");
		}
	}
	status = napi_create_buffer_copy(env, len, data, &data2, &buffer2);
	// napi_status napi_create_buffer(napi_env env, size_t size, void** data, napi_value* result)
	// napi_status napi_create_arraybuffer(napi_env env, size_t byte_length, void** data, napi_value* result)

	// printf("buffer_data: %s\n", (char *)data2);

	// napi_status napi_create_external(napi_env env, void* data, napi_finalize finalize_cb, void* finalize_hint, napi_value* result) // typeof result == napi_value // napi_get_value_external
	// napi_status napi_get_value_external(napi_env env, napi_value value, void** result)

	// napi_status napi_create_external_buffer(napi_env env, size_t length, void* data, napi_finalize finalize_cb, void* finalize_hint, napi_value* result)
	// napi_status napi_create_external_arraybuffer(napi_env env, void* external_data, size_t byte_length, napi_finalize finalize_cb, void* finalize_hint, napi_value* result)
	// void finalize_cb(napi_env env, void *data, void *hint)

	return buffer2;
}




typedef struct PObj_t{
	double v;
	napi_env env;
	napi_ref wrapper;
}PObj;
napi_value PObj_constructor(napi_env env) {
	void *data = NULL;
	napi_status status;
	napi_value val;
	status = napi_get_instance_data(env, &data);
	assert(status == napi_ok);
	status = napi_get_reference_value(env, *(napi_ref *)data, &val);
	assert(status == napi_ok);
	return val;
}
void PObj_destructor(napi_env env, void *data, void *hint) {
	napi_delete_reference(env, ((PObj *)data)->wrapper);
	free(data);
}
napi_value PObj_new(napi_env env, napi_callback_info info) {
	napi_status status;
	napi_value target;
	size_t argc = 1;
	napi_value argv[1];
	bool i;
	double v = 0;
	napi_value v2;
	napi_value jsthis;
	napi_valuetype t0;
	napi_value instance;
	PObj* obj;
	status = napi_get_new_target(env, info, &target);
	assert(status == napi_ok);
	if(target != NULL)
	{
		// new PObj(number)
		status = napi_get_cb_info(env, info, &argc, argv, &jsthis, NULL);
		assert(status == napi_ok);
		status = napi_typeof(env, argv[0], &t0);
		assert(status == napi_ok);
		if(t0 == napi_number) {
			status = napi_get_value_double(env, argv[0], &v);
			assert(status == napi_ok);
		}else if(t0 == napi_object) {
			status = napi_instanceof(env, argv[0], PObj_constructor(env), &i);
			assert(status == napi_ok);
			if(i)
			{
				status = napi_get_named_property(env, argv[0], "v", &v2);
				assert(status == napi_ok);
				status = napi_typeof(env, v2, &t0);
				assert(status == napi_ok);
				if(t0 == napi_number) {
					status = napi_get_value_double(env, v2, &v);
					assert(status == napi_ok);
				}
			}
		}
		obj = (PObj *)malloc(sizeof(PObj));
		assert(obj != NULL);
		obj->env = env;
		obj->v = v;
		status = napi_wrap(env, jsthis, (void *)obj, &PObj_destructor, NULL /* hint */, &obj->wrapper);
		assert(status == napi_ok);
		return jsthis;
	}
	else
	{
		status = napi_get_cb_info(env, info, &argc, argv, &jsthis, NULL);
		assert(status == napi_ok);
		status = napi_new_instance(env, PObj_constructor(env), argc, argv, &instance); // return new PObj_constructor(argv)
		assert(status == napi_ok);
		return instance;
	}
	return NULL;
}
napi_value PObj_getv(napi_env env, napi_callback_info info) {
	napi_status status;
	napi_value jsthis;
	PObj *obj;
	napi_value v;
	status = napi_get_cb_info(env, info, NULL, NULL, &jsthis, NULL);
	assert(status == napi_ok);
	status = napi_unwrap(env, jsthis, (void **)&obj);
	assert(status == napi_ok);
	status = napi_create_double(env, obj->v, &v);
	assert(status == napi_ok);
	return v;
}
napi_value PObj_setv(napi_env env, napi_callback_info info) {
	napi_status status;
	napi_value jsthis;
	PObj *obj;
	size_t argc = 1;
	napi_value argv[1];
	status = napi_get_cb_info(env, info, &argc, argv, &jsthis, NULL);
	assert(status == napi_ok);
	status = napi_unwrap(env, jsthis, (void **)&obj);
	assert(status == napi_ok);
	status = napi_get_value_double(env, argv[0], &obj->v);
	assert(status == napi_ok);
	return NULL;
}
napi_value PObj_plusOne(napi_env env, napi_callback_info info) {
	napi_status status;
	napi_value jsthis;
	PObj* obj;
	napi_value v;
	status = napi_get_cb_info(env, info, NULL, NULL, &jsthis, NULL);
	assert(status == napi_ok);
	status = napi_unwrap(env, jsthis, (void **)&obj);
	assert(status == napi_ok);
	obj->v += 1;
	status = napi_create_double(env, obj->v, &v);
	assert(status == napi_ok);
	return v;
}
void PObj_fin(napi_env env, void *data, void *hint) {
	napi_status status;
	status = napi_delete_reference(env, *(napi_ref *)data);
	assert(status == napi_ok);
	free((void *)data);
}
napi_value PObj_set(napi_env env, napi_value object) {
	napi_status status;
	napi_property_descriptor properties[] = {
		{"v", 0, 0, &PObj_getv, &PObj_setv, 0, napi_default, 0},
		{"plusOne", 0, &PObj_plusOne, 0, 0, 0, napi_default, 0}
	};
	napi_ref* _ref;
	napi_value obj;
	status = napi_define_class(env, "PObj", NAPI_AUTO_LENGTH, &PObj_new, NULL /* void* data */, 2, properties, &obj);
	assert(status == napi_ok);

	_ref = (napi_ref *)malloc(sizeof(napi_ref));
	assert(_ref != NULL);
	status = napi_create_reference(env, obj, 1, _ref);
	assert(status == napi_ok);
	status = napi_set_instance_data(env, _ref, &PObj_fin, NULL /* hint */);
	assert(status == napi_ok);
	napi_set_named_property(env, object, "PObj", obj);
	assert(status == napi_ok);
	return object;
}
int int_g = 0;
napi_value Init(napi_env env, napi_value exports) {
#define DESC(fn, f) {fn, 0, f, 0, 0, 0, napi_default, 0} // utf8name name method getter setter value atteibutes data
	napi_status status;
	napi_value fn;
	napi_property_descriptor desc[] = {
		DESC("testType", &testType), 
		DESC("testAsync", &async_testAsync), 
		DESC("copyBuffer", &test_copyBuffer), 
		DESC("loadFile", &f_testLoadFile), 
		DESC("nVersion", &test_nVersion)

	};
	// napi_property_descriptor desc = {"test", 0, Method, 0, 0, 0, napi_default, 0};
	status = napi_create_function(env, "test", NAPI_AUTO_LENGTH, Method, NULL, &fn);
	assert(status == napi_ok);
	status = napi_set_named_property(env, exports, "test", fn);
	assert(status == napi_ok);


	status = napi_define_properties(env, exports, sizeof(desc) / sizeof(napi_property_descriptor), desc);
	assert(status == napi_ok);

	PObj_set(env, exports);

	return exports;
}


NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)

