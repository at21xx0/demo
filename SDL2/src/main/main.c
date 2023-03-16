#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_thread.h"
#include "SDL_mixer.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define TEST_FONT "DroidSansFallback.ttf"

static jmp_buf jmpbuf;
static int err_line; 
#define JMP_ERROR 1
#define JMP_NOJMP 0
#define ERRE() \
	err_line = __LINE__, longjmp(jmpbuf, JMP_ERROR);

#define S_BLANK " "

int main2();
char *abs_path(char *f);
void testImg(SDL_Window *window, SDL_Surface *surface);
void testImg2(SDL_Renderer *renderer);
void testThread();
void testMus();
void testEvent(SDL_Renderer *ren);
int testQuit();
void testW();

int main(int argc, char *argv[])
{
	SDL_Window* window = NULL;
	SDL_Renderer *renderer = NULL; // 渲染器
	// SDL_Texture *tex = NULL; //
	SDL_Surface* screenSurface = NULL;
	(void)argc;
	(void)argv;

	switch(setjmp(jmpbuf))
	{
		case JMP_NOJMP:
			break;
		case JMP_ERROR:
			/* fallthough */
		default:
			fprintf(stderr, "%d: %s\n", err_line, SDL_GetError());
			if(window)
				SDL_DestroyWindow(window);
			SDL_Quit();
			exit(1);
			break;
	}
	// return main2();
	if (SDL_Init(SDL_INIT_VIDEO) < 0) // 初始化
		ERRE();
	// 初始化
	IMG_Init(IMG_INIT_PNG); //IMG_INIT_JPG 0| IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP;
	TTF_Init();


	// SDL_Surface *screenSurface = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_SWSURFACE);

	// 创建窗口
	window = SDL_CreateWindow("demo",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN); // title position_x position_y height width 可见
	// SDL_WINDOWPOS_UNDEFINED SDL_WINDOW_CENTER
	// SDL_WINDOW_OPENGL
	if (window == NULL)
		ERRE();

	screenSurface = SDL_GetWindowSurface(window);

	if (!screenSurface)
		ERRE();
	SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF)); // 填充
	SDL_UpdateWindowSurface(window); // 更新 surface
	testImg(window, screenSurface);
	SDL_Delay(1000);
	//
	SDL_FreeSurface(screenSurface);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	// SDL_RENDERER_PRESENTVSYNC
	testImg2(renderer);
	SDL_Delay(1000);
	SDL_RenderClear(renderer);
	// testThread();
	// testMus();
	testEvent(renderer);
	// SDL_Delay(1000);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	testW();
	TTF_Quit();
	IMG_Quit(); // 
	SDL_Quit();
	return 0;
}
int main2()
{
	SDL_Window* window = NULL;
	SDL_Renderer *renderer = NULL; // 渲染器
	SDL_Texture *tex = NULL; //
	SDL_Surface* surface = NULL;
	window = SDL_CreateWindow("demo", 0, 9, 400, 400, SDL_WINDOW_SHOWN); // title position_x position_y height width 可见
	if(window == NULL)
		ERRE();
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if(renderer == NULL)
		ERRE();
	surface = SDL_LoadBMP(abs_path("b.bmp"));
	if(renderer == NULL)
		ERRE();
	tex = SDL_CreateTextureFromSurface(renderer, surface);
	if(tex == NULL)
		ERRE();
	SDL_FreeSurface(surface);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, tex, NULL, NULL);
	SDL_RenderPresent(renderer); // 刷新
	// tex = IMG_LoadTexture(renderer, abs_path("c.bmp"));
	SDL_Delay(2000);
	SDL_DestroyTexture(tex);
	SDL_ShowSimpleMessageBox(0, "Mouse", "Left button was pressed!", window);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
#define ABS_BZ 1024
char abs_buf[ABS_BZ + 1] = {0};
int abs_len = 0;
char *abs_path(char *f)
{
	// mutex
	char *p;
	if(abs_len == 0)
	{
		p = SDL_GetBasePath();
		if(p == NULL)
		{
			strcpy(abs_buf, SDL_strdup("./"));
		}
		else
		{
			strcpy(abs_buf, p);
		}
		abs_len = strlen(abs_buf);
	}
	abs_buf[abs_len] = '\0';
	strncpy(abs_buf + abs_len, f, ABS_BZ - abs_len);
	abs_buf[ABS_BZ] = '\0';
	return abs_buf;
}
void testImg(SDL_Window *window, SDL_Surface *surface)
{
	// IMG_Init(IMG_INIT_PNG); //IMG_INIT_JPG 0| IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP;
	SDL_Surface *ori = NULL;
	SDL_Surface *img = NULL;
	SDL_Rect rec;

	// SDL_CreateRGBSurface(0, WIDTH, HEIGHT, 32, 0, 0, 0, 0); // flags, w, h, bits_depth r g b a

	
	ori = SDL_LoadBMP(abs_path("a.bmp")); // 每次显示可能都需要转换格式
	if(ori == NULL)
		ERRE();
	// img = SDL_DisplayFormat(ori); // 适合显示的格式
	img = SDL_ConvertSurfaceFormat(ori, SDL_PIXELFORMAT_RGBA8888, 0); // 适合显示的格式
	if(img == NULL)
		ERRE();
	SDL_FreeSurface(ori);

	rec.x = 20;
	rec.y = 100;
	SDL_BlitSurface(img, NULL, surface, &rec); // dest NULL source position // 
	rec.y = 10;
	SDL_BlitSurface(img, NULL, surface, &rec);
	SDL_FreeSurface(img);
	img = IMG_Load(abs_path("b.png"));
	// SDL_WM_SetCaption("Gloden", NULL);
	// apply_surface(0, 0, img, surface);
	rec.y = 180;
	SDL_BlitSurface(img, NULL, surface, &rec);
	SDL_FreeSurface(img);
	SDL_UpdateWindowSurface(window); // 更新 surface
	//IMG_Quit(); // 
}
//unsigned char utf8_look_for_table[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 1, 1};
static inline int get_u8n(unsigned char c)
{
	int n;
	/*
	if(c < 0xc0)
		n = 1;
	else if(c < 0xE0)
		n = 2;
	else if(c < 0xF0)
		n = 3;
	else if(c < 0xF8)
		n = 4;
	else if(c < 0xFC)
		n = 5;
	else if(c < 0xFE)
		n = 6;
	else
		n = 1;
	*/
	if((c & 0xC0) != 0xC0) // !(c & 0x80) || !(c & 0x40))
		n = 1;
	else if(!(c & 0x20))
		n = 2;
	else if(!(c & 0x10))
		n = 3;
	else if(!(c & 0x08))
		n = 4;
	else if(!(c & 0x04))
		n = 5;
	else if(!(c & 0x02))
		n = 6;
	else 
		n = 1;
	// return u8n_arr[c];
	return n;
}
void testImg2(SDL_Renderer *ren)
{
	SDL_Texture *tex;
	SDL_Surface *pic;
	SDL_Rect rect;
	SDL_Rect clip;
	SDL_Point p;
	uint32_t colorKey;
	TTF_Font *font;
	SDL_Color c;
	SDL_Surface *surface;
	int w;
	int h;
	int ct;
	int off;
	char test_text[64] = "三个字, test1, test2, test3, test4, test5";
	/*
	SDL_RWops *rw = SDL_RWFromMen(buf, bufsize); // 从内存读取 // SDL_RWFronConstMem
	// rw = SDL_RWFromFIle(fn, "r");
	// rw = SDL_RWFromFp(stdin, 0);
	pic = IMG_Load_RW(rw, 0); // src freesrc
	tex = IMG_LoadTexture_RW(rw, 0); 

	SDL_RWclose(rw);
	*/

	pic = IMG_Load(abs_path("c.png"));
	if(pic == NULL)
		ERRE();
	colorKey = SDL_MapRGB(pic->format, 0xDC, 0x96, 0x13);
	SDL_SetColorKey(pic, SDL_TRUE, colorKey); // 转为透明
	tex = SDL_CreateTextureFromSurface(ren, pic);
	if(tex == NULL)
		ERRE();

	rect.x = rect.y = 100;
	rect.w = rect.h = 0;
	SDL_QueryTexture(tex, NULL, NULL, (int *)&rect.w, (int *)&rect.h); // 查询图片大小
	SDL_RenderCopy(ren, tex, NULL, &rect);

	// tex = IMG_LoadTexture(renderer, abs_path("c.bmp"));

	clip.w = rect.w >> 1; // rect.w / 2
	clip.y = rect.y >> 1;
	clip.x = rect.w >> 2; // rect.w / 2
	clip.y = rect.y >> 2;

	rect.w = clip.w;
	rect.w = clip.w;
	rect.y = 200;
	SDL_RenderCopy(ren, tex, &clip, &rect);
	rect.x = 300;
	rect.w <<= 1;
	rect.h <<= 1;
	// p.x = rect.x + rect.w;
	// p.y = rect.y + rect.h;
	// p.x = p.y = 64;
	p.x = 32;
	p.y = 32;
	SDL_RenderCopyEx(ren, tex, NULL, &rect, 90.0, &p, SDL_FLIP_NONE); // 旋转角度 旋转中心 模式
	// SDL_FLIP_HORIZONTAL 水平旋转
	// SDL_FLIP_VERTICAL 垂直旋转
	// SDL_FLIP_NONE 不做任何处理
	/*
	double d = 0.0;
	for(int i = 0;i != 13;++i, d += 30.0)

		SDL_RenderCopyEx(ren, tex, NULL, &rect, d, &p, SDL_FLIP_NONE);
	*/
	SDL_FreeSurface(pic);
	SDL_DestroyTexture(tex);

	font = TTF_OpenFont(abs_path(TEST_FONT), 20);
	if(font == NULL)
		ERRE();
	c.r = c.b = c.a = 0;
	c.g = 200;
	// TTF_SetFontStyle(font, TTF_STYLE_BOLD | TTF_STYLE_ITALIC | TTF_STYLE_UNDERLINE | TTF_STYLE_STRIKETHROUGH);
	// TTF_GetFontStyle(font);
	surface = TTF_RenderUTF8_Blended(font, "test 测试", c); // Text UTF8 UNICOIDE // Blended Solid Shaded
	// surface = TTF_RenderText_Solid(font, "test", c); // TTF_RenderText_Shaded
	
	if(surface == NULL)
		ERRE();
	tex = SDL_CreateTextureFromSurface(ren, surface);
	SDL_FreeSurface(surface);

	SDL_QueryTexture(tex, NULL, NULL, (int *)&rect.w, (int *)&rect.h); // 查询图片大小
	SDL_RenderCopy(ren, tex, NULL, &rect);

	TTF_SizeUTF8(font, "test1  ", &w, &h);
	surface = TTF_RenderUTF8_Blended_Wrapped(font, test_text, c, (uint32_t)w);

	if(surface == NULL)
		ERRE();
	tex = SDL_CreateTextureFromSurface(ren, surface);
	SDL_FreeSurface(surface);

	SDL_QueryTexture(tex, NULL, NULL, (int *)&rect.w, (int *)&rect.h); // 查询图片大小
	rect.y += h;
	SDL_RenderCopy(ren, tex, NULL, &rect);
	
	// SDL_SetFontSize(font, 5);
	TTF_MeasureUTF8(font, test_text, (uint32_t)w, (int *)&rect.w, &ct); // font, text, limit_w, real_w, count
	// SDL_Log("%d %d %d", w, rect.w, ct);
	off = 0;
	do
	{
		off += get_u8n((unsigned char)test_text[off]);
	}
	while(--ct);
		
	test_text[off] = '\0';
	/*
	for(unsigned char i = 0;i != 255;++i)
	{
		SDL_Log("%u, %d, %d\n", i, utf8_look_for_table[i], get_u8n(i));
	}
	*/
	surface = TTF_RenderUTF8_Blended(font, test_text, c);

	if(surface == NULL)
		ERRE();
	tex = SDL_CreateTextureFromSurface(ren, surface);
	SDL_FreeSurface(surface);

	SDL_QueryTexture(tex, NULL, NULL, (int *)&rect.w, (int *)&rect.h); // 查询图片大小
	rect.y += h * 7;
	SDL_RenderCopy(ren, tex, NULL, &rect);

	TTF_CloseFont(font);

	SDL_DestroyTexture(tex);
	SDL_RenderPresent(ren);
}
int testThread_f(void *p)
{
	uint32_t t1, t2;
	int ct = 20;
	int frame = 60;
	uint32_t c = 1000 / frame;
	SDL_sem *sem = (SDL_sem *)p;
	SDL_SemWait(sem); // 等待
	while(--ct)
	{
		t1 = SDL_GetTicks();
		SDL_Delay(5);
		t2 = SDL_GetTicks();
		if(t2 - t1 < c)
			SDL_Delay(c + t2 - t1);
	}
	SDL_SemPost(sem);
	return 0;
}
struct testThread_pc
{
	int done;
	int item;
	SDL_mutex *loc;
	SDL_cond *cP;
	SDL_cond *cC;
};
SDL_mutex *testThread_l;
uint32_t testThread_item;
int testThread_producer(void *p)
{
	struct testThread_pc *h = (struct testThread_pc *)p;
	int ct = 0;
	while(!h->done)
	{
		SDL_Delay(rand() % 3);
		SDL_mutexP(h->loc);
		if(h->item > 300)
		{
			SDL_CondWait(h->cP, h->loc);
		}
		h->item += 40;
		SDL_mutexV(h->loc);
		SDL_CondSignal(h->cC);
		++ct;
	}
	return ct;
}
int testThread_consumer(void *p)
{
	struct testThread_pc *h = (struct testThread_pc *)p;
	int ct = 0;
	while(!h->done)
	{
		SDL_Delay(rand() % 3);
		SDL_mutexP(h->loc);
		if(h->item < 50)
		{
			SDL_CondWait(h->cC, h->loc);
		}
		h->item -= 47;
		SDL_mutexV(h->loc);
		SDL_CondSignal(h->cP);
		++ct;
		if(ct > 200)
			h->done = 1;
	}
	return ct;
}
void testThread()
{
	SDL_Thread *th1;
	SDL_Thread *th2;
	uint32_t t1;
	uint32_t t2;
	SDL_sem *sem; // 上锁前最多有几个线程可通过
	struct testThread_pc h;
	sem = SDL_CreateSemaphore(1);
	t1 = SDL_GetTicks();
	th1 = SDL_CreateThread(testThread_f, "th", (void *)sem);
	th2 = SDL_CreateThread(testThread_f, "th", (void *)sem);
	SDL_WaitThread(th1, NULL);
	SDL_WaitThread(th2, NULL);
	t2 = SDL_GetTicks();
	SDL_Log("%u %u", 20, (t2 - t1) / (1000 / 60));
	SDL_DestroySemaphore(sem);

	h.loc = SDL_CreateMutex();
	h.item = 0;
	h.done = 0;
	h.cC = SDL_CreateCond();
	h.cP = SDL_CreateCond();
	srand(SDL_GetTicks());
	th1 = SDL_CreateThread(testThread_producer, "th", (void *)&h);
	th2 = SDL_CreateThread(testThread_consumer, "th", (void *)&h);
	SDL_WaitThread(th1, (int *)&t1);
	SDL_WaitThread(th2, (int *)&t2);
	SDL_Log("%u %u", t1, t2);
	SDL_LockMutex(h.loc);
	SDL_UnlockMutex(h.loc);
	SDL_DestroyMutex(h.loc);
	SDL_DestroyCond(h.cC);
	SDL_DestroyCond(h.cP);
}
void testMus()
{
	// Mix_Chunk *chu; // 片段
	Mix_Music *mus; // 较长
	int i;
	// int channel;
	i = Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096); // freqency format channels chunksize // 初始化
	if(i != 0)
		return;
	//chu = Mix_LoadMUS(file); // WAV OGG MP3
	// chu = Mix_LoadWAV_RW(SDL_RWFromFile(abs_path("mus.wav"), "rb"), 1);
	mus = Mix_LoadMUS(abs_path("mus.wav"));
	if(!mus)
	{
		SDL_Log("%s", Mix_GetError());
		goto testMus_end;
	}
	Mix_PlayMusic(mus,-1); // loop 永不停止 // 如果有其他已播放，暂停其他再开始
	SDL_Delay(20000);
	Mix_PauseMusic();
	// Mix_FadeOutMusic();
	// Mix_HaltMusic();
	// Mix_ResumeMusic();
	// Mix_PlayChannelTimeout(channel, mus, 1, -1 / * ticks * /);
	// Mix_FreeChunk(chu);
	/*
	channel = Mix_PlayChannel(-1, chu, 0); // channel, chunk, loops
	if(Mix_Playing(channel)) // Mix_Paused
		Mix_Pause(channel);
	Mix_Resume(channel);

	// int Mix_VolumeChunk(Mix_Chunk *chunk, int volume);
	 */
	Mix_FreeMusic(mus);
testMus_end:
	Mix_CloseAudio();
	Mix_Quit();
}
struct tlog_t
{
	TTF_Font *font;
	int x;
	int y;
	SDL_Color c;
	SDL_Renderer *ren;
	int fontSize;
};
void tlog(struct tlog_t *h, const char *format, ...)
{
#define S_BUFSIZE 1024
	char buf[S_BUFSIZE];
	va_list ap;
	SDL_Surface *surface;
	SDL_Texture *tex;
	SDL_Rect rect;
	if(h->font == NULL)
	{
		h->font = TTF_OpenFont(abs_path(TEST_FONT), 20);
		if(h->font == NULL)
			ERRE();
	}
	if(format == NULL)
	{
		TTF_CloseFont(h->font);
		h->font = NULL;
		return;
	}
	va_start(ap, format);
	buf[0] = '\0';
	vsnprintf(buf, S_BUFSIZE, format, ap);
	va_end(ap);
	//SDL_Log(buf);
	surface = TTF_RenderUTF8_Blended(h->font, buf, h->c);
	if(surface == NULL)
		ERRE();
	tex = SDL_CreateTextureFromSurface(h->ren, surface);
	if(tex == NULL)
		ERRE();
	SDL_FreeSurface(surface);

	SDL_QueryTexture(tex, NULL, NULL, (int *)&rect.w, (int *)&rect.h); // 查询图片大小
	rect.x = h->x;
	rect.y = h->y;
	SDL_SetRenderDrawColor(h->ren, 0x00, 0x00, 0x00, 0x00);
	rect.w += h->fontSize;
	SDL_RenderFillRect(h->ren, &rect);
	rect.w -= h->fontSize;
	SDL_RenderCopy(h->ren, tex, NULL, &rect);
	SDL_DestroyTexture(tex);
	SDL_RenderPresent(h->ren);
}
void testEvent(SDL_Renderer *ren)
{
	SDL_Event event;
	int done = 0;
	struct tlog_t h;
	char *m, *n, c;
	SDL_Rect rect;
	rect.x = 0;
	rect.y = 380;
	rect.w = 640;
	rect.h = 100;
	SDL_SetRenderDrawColor(ren, 0x64, 0x00, 0x00, 0x00);
	SDL_RenderFillRect(ren, &rect);
	h.c.r = h.c.g = h.c.b = h.c.a = 0;
	h.c.g = 200;
	h.fontSize = 6;
	h.font = NULL;
	h.ren = ren;
	h.x = h.y = 20;
	tlog(&h, "test");
	// SDL_Log("tt %d\n", 5);
	// SDL_EnableKeyRepeat(time, interval);
	while(!done)
	{
		while(SDL_PollEvent(&event)) // SDL_WaitEvent SDL_WaitEventTimeout SDL_PushEvent
		{
			switch(event.type)
			{
				case SDL_MOUSEBUTTONDOWN:
					/* fallthrough */
				case SDL_MOUSEBUTTONUP:
					switch(event.button.button)
					{
						case SDL_BUTTON_LEFT:
							c = '<';
							break;
						case SDL_BUTTON_MIDDLE:
							c = '|';
							break;
						case SDL_BUTTON_RIGHT:
							c = '>';
							break;
							/*
						case SDL_BUTTON_WHEELUP:
							c = '^';
							break;
						case SDL_BUTTON_WHEELDOWN:
							c = 'V';
							break;
							*/
						default:
							c = ' ';
							break;
					}
					if(event.button.type == SDL_MOUSEBUTTONDOWN)
						m = "down";
					else if(event.button.type == SDL_MOUSEBUTTONUP)
						m = "up";
					else
						m = S_BLANK;
					// uint32_t SDL_GetWindowID(window);
					tlog(&h, "mousebutton %c %s %u,%u %u %u", c, m, event.button.x, event.button.y, event.button.clicks, event.button.windowID);
					if(event.button.y > 380)
						done = 1;
					/*
					int x; 
					int y;
					if(SDL_GetMouseState(&x,&y) == SDL_BUTTON(SDL_BUTTON_WHEELUP))
						tlog(&h, "%d %d\n", x, y);
						*/
					break;
				case SDL_MOUSEMOTION:
					tlog(&h, "motion  %u,%u %d,%d  %u", event.motion.x, event.motion.y, event.motion.xrel, event.motion.yrel, event.motion.windowID);
					break;
				case SDL_MOUSEWHEEL:
					tlog(&h, "mousewheel: %d,%d %u", event.wheel.x, event.wheel.y, event.wheel.timestamp);
					// float preciseX
					break;
				case SDL_KEYDOWN:
					/* fallthrough */
				case SDL_KEYUP:
					/* fallthrough */
					if(event.key.type == SDL_KEYDOWN)
						m = "keydown";
					else if(event.key.type == SDL_KEYUP)
						m = "keyup";
					else
						m = S_BLANK;
					if(event.key.state == SDL_PRESSED)
						n = "pressed";
					else if(event.key.state == SDL_RELEASED)
						n = "released";
					else
						n = S_BLANK;
					switch(event.key.keysym.sym)
					{
						case SDLK_0:
							c = '0';
							break;
						case SDLK_a:
							c = 'a';
							break;
						case 'b':
							c = 'b';
							break;
						case SDLK_F1:
							c = '1';
							break;
						case SDLK_UP:
							c = '^';
							break;
						case SDLK_DOWN:
							c = 'v';
							break;
						case SDLK_LEFT:
							c = '<';
							break;
						case SDLK_RIGHT:
							c = '>';
							break;
						//case SDLK_LCTRL:
						case SDLK_q:
							c = 'q';
							done = 1;
							break;
						default:
							c = (char)event.key.keysym.sym;
							if(event.key.keysym.sym > 255)
								c = ' ';
							if((c < 'a' && c > 'z') || (c < '0' && c > '9'))
								c = ' ';
							break;
					}
					tlog(&h, "KEY_%c_%s_%s sc:%u %s sym:%u wID:%u", c, m, n, event.key.keysym.scancode, SDL_GetKeyName(event.key.keysym.sym), event.key.keysym.sym, event.key.windowID); // event.key.keysym.unicode
					if(event.key.keysym.mod == KMOD_RCTRL) // NONE, LSHIFT, RSHIFT, SHIFT, LCTRL, RCTRL, CTRL, LALT, RALT, ALT, NUM, CAPS, MODDE, SCROLL,   | &
					{
						SDL_SetModState(KMOD_NONE);
					}
					break;
				case SDL_TEXTINPUT:
					tlog(&h, "input: %s", event.text.text);
					// SDL_StopTextInput();
					// SDL_StartTextInput();
					// SDL_IsTextInputActive();
					break;
				case SDL_TEXTEDITING:
					tlog(&h, "inputing: %s %d %d", event.edit.text, event.edit.start, event.edit.length);
					break;
				case SDL_KEYMAPCHANGED:
					/* fallthrough */
				case SDL_TEXTEDITING_EXT:
					if(event.key.type == SDL_KEYMAPCHANGED)
						m = "keymapchanged";
					else if(event.key.type == SDL_TEXTEDITING_EXT)
						m = "textediting_ext";
					else
						m = S_BLANK;
					//tlog(&h, "%s", m);
					break;
				case SDL_FINGERUP:
					/* fallthrough */
				case SDL_FINGERDOWN:
					/* fallthrough */
				case SDL_FINGERMOTION:
					if(event.tfinger.type == SDL_FINGERUP)
						m = "up";
					else if(event.tfinger.type == SDL_FINGERDOWN)
						m = "down";
					else if(event.tfinger.type == SDL_FINGERMOTION)
						m = "motion";
					else
						m = S_BLANK;

					tlog(&h, "finger %s %f,%f %f,%f", m, event.tfinger.x, event.tfinger.y, event.tfinger.dx, event.tfinger.dy);
					break;
				case SDL_WINDOWEVENT:
					switch(event.window.event)
					{
						case SDL_WINDOWEVENT_NONE:
							break;
						case SDL_WINDOWEVENT_SHOWN:
							tlog(&h, "shown");
							break;
						case SDL_WINDOWEVENT_HIDDEN:
							tlog(&h, "hidden");
							break;
						case SDL_WINDOWEVENT_EXPOSED:
							tlog(&h, "exposed"); // 窗口被挡住又显示，需要重绘
							break;
						case SDL_WINDOWEVENT_RESTORED:
							tlog(&h, "restored");
							break;
						case SDL_WINDOWEVENT_MOVED:
							tlog(&h, "moved %u, %u", event.window.data1, event.window.data2);
							break;
						case SDL_WINDOWEVENT_RESIZED:
							tlog(&h, "resize %u, %u", event.window.data1, event.window.data2);
							break;
						case SDL_WINDOWEVENT_SIZE_CHANGED:
							tlog(&h, "size_changed %u,%u ", event.window.data1, event.window.data2);
							// 拖动或者调用了API
							break;
						case SDL_WINDOWEVENT_MINIMIZED:
							tlog(&h, "min"); // 最小化
							break;
						case SDL_WINDOWEVENT_MAXIMIZED:
							tlog(&h, "max"); // 最大化
							break;
						case SDL_WINDOWEVENT_ENTER:
							tlog(&h, "mouse_focus ENTER");
							break;
						case SDL_WINDOWEVENT_LEAVE:
							tlog(&h, "mouse_unfocus LEAVE");
							break;
						case SDL_WINDOWEVENT_FOCUS_GAINED:
							tlog(&h, "key_fouse_gained");
							break;
						case SDL_WINDOWEVENT_FOCUS_LOST:
							tlog(&h, "key_fouse_lost");
							break;
						case SDL_WINDOWEVENT_CLOSE:
							// 关闭窗口
							done = 1;
							// event.type = SDL_Quit;
							// SDL_PushEvent(&event);
							break;
						default:
							break;
					}
					break;
				case SDL_QUIT:
					done = 1;
					break;
				default:
					tlog(&h, "unknow: %u\n", event.type);
					break;
			}
		}
		SDL_Delay(5);


	}
	/*
	uint8_t *keystates = SDL_GetKeyState(NULL);
	// GetModState GetMouseState JoystickGetAxis
	if(keystates[SDLK_UP])
	{
		SDL_Log("up\n");
	}
	*/
	tlog(&h, NULL);
}
int testQuit()
{
	TTF_Font *font;
	SDL_Window *win;
	SDL_Renderer *ren; // 渲染器
	SDL_Texture *tex; //
	SDL_Surface *surface;
	SDL_Surface *s2;
	SDL_Color c;
	SDL_Event e;
	SDL_Point p;
	int q;
	SDL_Rect y;
	SDL_Rect n;
	int w, h;
	SDL_Rect a;
	uint32_t t1, t2;
	int frame = 60;
	uint32_t wID;
	uint32_t cc = 1000 / frame;
	win = SDL_CreateWindow("Quit? ", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 350, 150, SDL_WINDOW_SHOWN);
	if(win == NULL)
		ERRE();
	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	if(ren == NULL)
		ERRE();
	font = TTF_OpenFont(abs_path(TEST_FONT), 18);
	if(font == NULL)
		ERRE();

	SDL_GetWindowSize(win, &w, &h);
	// SDL_GetWindowPositon(win, &x, &y);
	// SDL_ShowWindow
	wID = SDL_GetWindowID(win);
	s2 = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);
	SDL_FillRect(s2, NULL, SDL_MapRGB(s2->format, 0xFF, 0xFF, 0xFF)); // ??
	c.r = c.g = c.b = c.a = 0;
	y.w = w / 5;
	y.h = h / 5;
	y.x = y.w;
	y.y = h - y.h - y.h;
	n.w = y.w;
	n.h = y.h;
	n.x = y.w * 3;
	n.y = y.y;
	//SDL_FillRect(s2, &n, SDL_MapRGB(s2->format, 0x00, 0x00, 0x00));
	//SDL_FillRect(s2, &y, SDL_MapRGB(s2->format, 0x00, 0x00, 0x00));
	memcpy(&a, &y, sizeof(SDL_Rect));
	surface = TTF_RenderUTF8_Blended(font, "yes", c);
	if(surface == NULL)
		ERRE();
	q = 2;
	while(1)
	{
		SDL_FillRect(s2, &a, SDL_MapRGB(s2->format, 0x00, 0x00, 0x00));
		a.x += 1;
		a.y += 1;
		a.w -= 2;
		a.h -= 2;
		SDL_FillRect(s2, &a, SDL_MapRGB(s2->format, 0xEF, 0xEF, 0xEF)); a.x += a.w / 2;
		a.w = surface->w;
		a.x -= a.w / 2;
		a.y += a.h / 2;
		a.h = surface->h;
		a.y -= a.h / 2;
		SDL_BlitSurface(surface, NULL, s2, &a);
		SDL_FreeSurface(surface);
		if(--q == 0)
			break;
		surface = TTF_RenderUTF8_Blended(font, "no", c);
		if(surface == NULL)
			ERRE();
		memcpy(&a, &n, sizeof(SDL_Rect));
	}
	SDL_RenderClear(ren);
	tex = SDL_CreateTextureFromSurface(ren, s2);
	TTF_CloseFont(font);

	q = 2;
	while(q == 2)
	{
		t1 = SDL_GetTicks();
		while(SDL_WaitEventTimeout(&e, 5))
		{
			/*
			if(Window.UserEvent.windowID != wID)
				SDL_PushEvent(&e);
			*/
			switch(e.type)
			{
				case SDL_KEYUP:
					if(e.key.windowID != wID)
						break;
					switch(e.key.keysym.sym)
					{
						case SDLK_n:
							/* fallthrough */
						case SDLK_ESCAPE:
							q = 0;
							break;
						case SDLK_y:
							/* fallthrough */
						case SDLK_RETURN: // ENTER
							q = 1;
							break;
						default:
							break;
					}
					break;
				case SDL_TEXTEDITING:
					SDL_StopTextInput();
					break;
				case SDL_FINGERUP:
					if(e.tfinger.windowID != wID)
						break;
					e.button.x = (uint32_t)(e.tfinger.x * w);
					e.button.y = (uint32_t)(e.tfinger.y * h);
					/* fallthrough */
				case SDL_MOUSEBUTTONUP:
					if(e.button.windowID != wID)
						break;
					if(e.button.windowID != wID)
						break;
					p.x = e.button.x;
					p.y = e.button.y;
					if(e.button.button != SDL_BUTTON_LEFT)
						(void)e;
					else if(SDL_PointInRect(&p, &y))
						q = 1;
					else if(SDL_PointInRect(&p, &n))
						q = 0;
					break;
				case SDL_WINDOWEVENT:
					if(e.window.event != SDL_WINDOWEVENT_CLOSE)
							break;
					/* fallthrough */
				case SDL_QUIT:
					q = 0;
					break;
			}
		}
		SDL_RenderCopy(ren, tex, NULL, NULL);
		SDL_RenderPresent(ren);
		t2 = SDL_GetTicks();
		if(t2 - t1 < cc)
			SDL_Delay(cc + t2 - t1);
	}
	SDL_DestroyTexture(tex);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);

	return q;
}
typedef struct button_t
{
	SDL_Rect z;
	// SDL_Surface *surface;
	SDL_Texture *tex;
	// int (*pf)(Btn *);
	int display;
}Btn;
typedef struct button_info
{
	SDL_Renderer *ren;
	TTF_Font *font;
	int border;
	SDL_Color cb;
	SDL_Color cf;
	SDL_Color c;
}Btn_info;
int btn_create(Btn *h, Btn_info *info, SDL_Rect *z, char *text, int display)
{
	SDL_Rect a;
	SDL_Surface *s;
	SDL_Surface *f;
	if(!h || ! z || !info || !text || !info->font)
		return 1;
	memcpy(&h->z, z, sizeof(SDL_Rect));
	a.x = a.y = 0;
	a.w = z->w;
	a.h = z->h;
	s = SDL_CreateRGBSurface(0, a.w, a.h, 32, 0, 0, 0, 0);
	if(s == NULL)
	{
		goto btn_create_err;
	}
	f = TTF_RenderUTF8_Blended(info->font, text, info->c);
	if(f == NULL)
	{
		SDL_FreeSurface(s);
		goto btn_create_err;
	}
	h->display = display;
	SDL_FillRect(s, &a, *(uint32_t *)(&info->cb));
	a.x += info->border;
	a.y += info->border;
	a.w -= info->border << 1;
	a.h -= info->border << 1;
	SDL_FillRect(s, &a, *(uint32_t *)(&info->cf));
	a.x += a.w >> 1;
	a.w = f->w;
	a.x -= a.w >> 1;
	a.y += a.h >> 1;
	a.h = f->h;
	a.y -= a.h >> 1;
	SDL_BlitSurface(f, NULL, s, &a);
	SDL_FreeSurface(f);
	h->tex = SDL_CreateTextureFromSurface(info->ren, s);
	SDL_FreeSurface(s);
	if(!h->tex)
	{
		goto btn_create_err;
	}

	return 0;
btn_create_err:
	return 1;
}
void btn_copy(Btn *h, Btn_info *info)
{
	if(!h || h->display == 0 || !h->tex)
		return;
	SDL_RenderCopy(info->ren, h->tex, NULL, &h->z);

}
void btn_show(Btn *h)
{
	if(h)
		h->display = 1;
}
void btn_hide(Btn *h)
{
	if(h)
		h->display = 0;
}
static inline int btn_xy(Btn *h, int x, int y)
{
	SDL_Point p;
	p.x = x;
	p.y = y;
	return h->display && SDL_PointInRect(&p, &h->z);
}
void btn_free(Btn *h)
{
	if(!h || !h->tex)
		return;
	SDL_DestroyTexture(h->tex);
	h->tex = NULL;
}

typedef enum{
	BTN_QUIT,
	BTN_FULLOFF,
	BTN_FULLON,
	BTN_BORDEROFF,
	BTN_BORDERON,
	BTN_B1,
	BTN_B2,
	BTN_TITLE,
	BTN_COPY,
	BTN_PASTE,
	BTN_TOTAL
}testW_btn;

#define INPUT_BZ 4096

static void str_replace(char *d, const int d_rl, const char *s)
{
	int d_len = strlen(d);
	int s_len = strlen(s);
	char *m;
	const char *n;
	// if(d_rl > d_len) return;
	if(s_len > d_rl)
	{
		n = d + d_len;
		m = (char *)n + s_len - d_rl;
		d += d_rl - 1;
		while(n != d)
		{
			*m = *n;
			--n;
			--m;
		}
		d -= d_rl - 1;
	}
	else if(s_len < d_rl)
	{
		n = d + d_rl;
		m = d + s_len;
		d += s_len + d_len;
		while(m != d)
		{
			*m = *n;
			++n;
			++m;
		}
		d -= s_len + d_len;
	}
	m = d;
	n = s;
	d += s_len;
	while(m != d)
	{
		*m = *n;
		++m;
		++n;
	}
	// d -= s_len;
}

#define str_insert(d, s) str_replace(d, 0, s)
#define str_erase(d, n) str_replace(d, n, "");
int get_u8r(char *s)
{
	return get_u8n((unsigned char)*s);
}
int get_u8l(char *s, int l)
{
	char *m;
	int i;
	if(l > 7)
		m = s - 7;
	else
		m = s - l;
	do
	{
		i = get_u8r(m);
		m += i;
	}
	while(m < s);
	return i;
}

void testW()
{
	SDL_Window *win = NULL;
	SDL_Renderer *ren = NULL; // 渲染器
	SDL_Texture *tex = NULL; //
	TTF_Font *font = NULL;
	SDL_Color c;
	SDL_Event e;
	SDL_Point p;
	int w, h;
	uint32_t wID;
	Btn b[BTN_TOTAL];
	Btn_info info;
	SDL_Rect a;
	int i;

	char buf[INPUT_BZ];
	char ch;
	SDL_Rect text;
	int cursor = 0;
	char *m;
	//char *n;
	int old_textediting_length = 0;
	int j;
	int text_off_x = 0;
	int text_update = 1;
	SDL_Surface *text_s = NULL;
	SDL_Surface *text_bg = NULL;
	int cursor_width = 1;
	int cursor_display = 0;
	// int select_cursor;

	int frame = 60;
	uint32_t t1, t2;
	uint32_t cc = 1000 / frame;
	int done = 0;
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();
	win = SDL_CreateWindow("window ", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if(win == NULL)
		goto testW_err;
	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	if(ren == NULL)
		goto testW_err;
	font = TTF_OpenFont(abs_path(TEST_FONT), 18);
	if(font == NULL)
		goto testW_err;

	SDL_GetWindowSize(win, &w, &h);
	wID = SDL_GetWindowID(win);
	info.font = font;
	info.ren = ren;
	c.a = 0xFF;
	c.r = c.g = c.b  = 0x00;
	info.cb = info.c = c;
	c.r = c.g = c.b = 0xEF;
	info.cf = c;
	info.border = 1;
	a.w = 200;
	a.h = 32;
	a.x = 10;
	a.y = 10;
	btn_create(b + BTN_QUIT, &info, &a, "quit", 1);
	a.y = 52;
	btn_create(b + BTN_FULLOFF, &info, &a, "fullscreen [OFF]", 1);
	btn_create(b + BTN_FULLON, &info, &a, "fullscreen [ON]", 0);
	a.y += 42;
	btn_create(b + BTN_BORDEROFF, &info, &a, "border [OFF]", 0);
	btn_create(b + BTN_BORDERON, &info, &a, "border [ON]", 1);
	a.y += 42;
	btn_create(b + BTN_B1, &info, &a, "B1", 1);
	a.y += 42;
	btn_create(b + BTN_B2, &info, &a, "B2", 1);
	a.y += 42;
	btn_create(b + BTN_TITLE, &info, &a, "setTitle", 1);
	a.y += 42;
	btn_create(b + BTN_COPY, &info, &a, "copy", 1);
	a.y += 42;
	btn_create(b + BTN_PASTE, &info, &a, "paste", 1);
	SDL_Cursor *cur = NULL;
	SDL_Surface *surface;
	a.x = 300;
	a.y = 200;
	a.h = 400;
	a.w = 200;
	c.g = 0;
	c.r = c.b = 0;
	text.x = 300;
	text.y = 30;
	text.w = 200;
	TTF_SizeUTF8(font, "0", NULL, &text.h);
	text.h += 2;


	surface = TTF_RenderUTF8_Blended(font, "0", c);
	SDL_SetWindowIcon(win, surface);
	SDL_FreeSurface(surface);

	SDL_SetWindowResizable(win, SDL_TRUE);
	SDL_SetWindowTitle(win, "title");
	//SDL_SetWindowPosition(win, 100, 100);
	//SDL_SetWindowSize(win, 100, 100);
	//SDL_SetWindowOpacity(win, 0.5); // 半透明
	SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
	SDL_SetHint(SDL_HINT_IME_INTERNAL_EDITING, "1");
	buf[0] = '\0';
	// SDL_Log("path: %s", SDL_GetBasePath());// SDL_GetPrefPath(const char *org, const char *app);
	while(!done)
	{
		t1 = SDL_GetTicks();
		SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(ren);
		if(text_update)
		{
			text_update = 0;
			if(text_bg == NULL && (text_bg = SDL_CreateRGBSurface(0, text.w, text.h, 32, 0, 0, 0, 0)) == NULL)
				goto testW_err;
			SDL_FillRect(text_bg, NULL, SDL_MapRGB(text_bg->format, 0x00, 0x00, 0x00));
			a.w = text.w - 2;
			a.h = text.h - 2;
			a.x = a.y = 1;
			SDL_FillRect(text_bg, &a, SDL_MapRGB(text_bg->format, 0xFF, 0xFF, 0xFF));
			if(cursor_display)
			{
				ch = buf[cursor];
				buf[cursor] = '\0';
				TTF_SizeUTF8(font, buf, &i, &j);
				buf[cursor] = ch;
				a.x = 1 + i;
				a.y = 1;
				a.h = j;
				if(cursor_width == 0)
				{
					j = cursor + get_u8r(buf + cursor);
					ch = buf[j];
					buf[j] = '\0';
					TTF_SizeUTF8(font, buf + cursor, &i, NULL);
					a.w = i;
					buf[j] = ch;
				}
				else
				{
					a.w = cursor_width;
				}
				text_off_x = 0;
				if(a.x + a.w > text.w)
				{
					text_off_x = a.x;
					a.x = text.w - a.w;
					text_off_x -= a.x;
				}
				SDL_FillRect(text_bg, &a, SDL_MapRGB(text_bg->format, 0xBF, 0xBF, 0xBF));
				a.x += text.x;
				a.y += text.y;
				SDL_SetTextInputRect(&a);
			}
			else
				text_off_x = 0;
			a.w = text.w - 2;
			a.h = text.h - 2;
			a.x = a.y = 1;
			if(buf[0] != '\0')
			{
				text_s = TTF_RenderUTF8_Blended(font, buf, c);
				if(!text_s)
					goto testW_err;
				a.x = 1 - text_off_x;
				a.w = text_s->w;
				a.y += a.h >> 1;
				a.h = text_s->h;
				a.y -= a.h >> 1;
				SDL_BlitSurface(text_s, NULL, text_bg, &a);
				SDL_FreeSurface(text_s);
			}
			if(tex)
				SDL_DestroyTexture(tex);
			tex = SDL_CreateTextureFromSurface(ren, text_bg);
			if(tex == NULL)
				goto testW_err;
		}
		SDL_RenderCopy(ren, tex, NULL, &text);
		for(i = 0; i != BTN_TOTAL;++i)
		{
			btn_copy(b + i, &info);
		}
		SDL_RenderPresent(ren);
		while(SDL_PollEvent(&e))
		{
			/*
			if(Window.UserEvent.windowID != wID)
				SDL_PushEvent(&e);
			*/
			switch(e.type)
			{
				case SDL_KEYDOWN:
					if(e.key.windowID != wID)
						break;
					switch(e.key.keysym.sym)
					{
						case SDLK_n:
							/* fallthrough */
							break;
						case SDLK_ESCAPE:
							break;
						case SDLK_BACKSPACE:
							if(cursor_display && cursor != 0)
							{
								j = get_u8l(buf  + cursor, cursor);
								str_erase(buf + cursor - j, j);
								cursor -= j;
								text_update = 1;
							}
							break;
						case SDLK_RIGHT:
							if(cursor_display && buf[cursor] != '\0')
							{
								j = get_u8r(buf  + cursor);
								cursor += j;
								text_update = 1;
							}
							break;
						case SDLK_LEFT:
							if(cursor_display && cursor != 0)
							{
								j = get_u8l(buf  + cursor, cursor);
								cursor -= j;
								text_update = 1;
							}
							break;
						case SDLK_RETURN: // ENTER
							break;
						default:
							break;
					}
					break;
				case SDL_FINGERDOWN:
					if(e.button.windowID != wID)
						break;
					e.button.x = (int)(e.tfinger.x * w);
					e.button.y = (int)(e.tfinger.y * h);
					/* fallthrough */
				case SDL_MOUSEBUTTONDOWN:
					if(e.button.windowID != wID)
						break;
					p.x = e.button.x;
					p.y = e.button.y;
					if(e.button.button == SDL_BUTTON_LEFT)
					{
						if(SDL_PointInRect(&p, &text))
						{
							if(!SDL_IsTextInputActive())
								SDL_StartTextInput();
#if 1
							TTF_MeasureUTF8(font, buf, p.x - text.x + text_off_x, NULL, &j);
							i = 0;
							if(j > 0)
							{
								do
								{
									i += get_u8r(buf + i);
								}
								while(--j);
							}
							cursor = i;
#endif
							cursor_display = 1;
							text_update = 1;
						}
						else
						{
							SDL_StopTextInput();
							cursor_display = 0;
							text_update = 1;
						}
					}
					break;
				case SDL_TEXTINPUT:
					if(!cursor_display)
						break;
					// SDL_Log("input %s", e.text.text);
					str_insert(buf + cursor, e.text.text);
					cursor += strlen(e.text.text);
					text_update = 1;
					break;
				case SDL_TEXTEDITING:
					if(!cursor_display)
						break;
					// SDL_Log("editing: %s %d %d %d", e.edit.text, e.edit.start, e.edit.length, old_textediting_length);
					str_replace(buf + cursor, old_textediting_length, e.edit.text);
					old_textediting_length = e.edit.start;
					text_update = 1;
					break;
				case SDL_FINGERUP:
					if(e.button.windowID != wID)
						break;
					e.button.x = (uint32_t)(e.tfinger.x * w);
					e.button.y = (uint32_t)(e.tfinger.y * h);
					/* fallthrough */
				case SDL_MOUSEBUTTONUP:
					if(e.button.windowID != wID)
						break;
					if(e.button.button != SDL_BUTTON_LEFT)
						break;
					for(i = 0;i != BTN_TOTAL && !btn_xy(b + i, e.button.x, e.button.y);++i);
					switch(i)
					{
						case BTN_QUIT:
							e.type = SDL_QUIT;
							SDL_PushEvent(&e);
							break;
						case BTN_FULLOFF:
							SDL_SetWindowFullscreen(win, SDL_TRUE);
							btn_show(b + BTN_FULLON);
							btn_hide(b + BTN_FULLOFF);
							break;
						case BTN_FULLON:
							SDL_SetWindowFullscreen(win, SDL_FALSE);
							btn_show(b + BTN_FULLOFF);
							btn_hide(b + BTN_FULLON);
							break;
						case BTN_BORDEROFF:
							SDL_SetWindowBordered(win, SDL_TRUE);
							btn_show(b + BTN_BORDERON);
							btn_hide(b + BTN_BORDEROFF);
							break;
						case BTN_BORDERON:
							SDL_SetWindowBordered(win, SDL_FALSE);
							btn_show(b + BTN_BORDEROFF);
							btn_hide(b + BTN_BORDERON);
							break;
						case BTN_B1:
							cur = SDL_CreateSystemCursor( SDL_SYSTEM_CURSOR_WAIT);  // SDL_CreateColorCursor(surface, hot_x, hot_y) 从surface SDL_CreateCursor(const Uint8 *data, const Uint8* mask, int w, int h, int hot_x, int hot_y) 从像素 SDL_GetCursor() 当前 SDL_GetDefaultCursor() SDL默认
							// SDL_Mouse.h
							SDL_SetCursor(cur);
							SDL_Delay(1000);
							SDL_FreeCursor(cur);
							break;
						case BTN_B2:
							SDL_ShowCursor(SDL_DISABLE);
							SDL_Delay(1000);
							if(!SDL_ShowCursor(SDL_QUERY))
							{
								SDL_ShowCursor(SDL_ENABLE);
							}
							break;
						case BTN_TITLE:
							SDL_SetWindowTitle(win, buf);
							break;
						case BTN_COPY:
							if(*buf != '\0')
								SDL_SetClipboardText(buf);
							break;
						case BTN_PASTE:
							if(SDL_HasClipboardText())
							{
								m = SDL_GetClipboardText();
								strncpy(buf, m, INPUT_BZ - 1);
								buf[INPUT_BZ - 1] = '\0';
								SDL_free(m);
								cursor = strlen(buf);
								text_update = 1;
							}
						case BTN_TOTAL:
							/* fallthrough */
						default:
							break;
					}
					break;
				case SDL_WINDOWEVENT:
					if(e.window.event == SDL_WINDOWEVENT_FOCUS_GAINED)
					{
						// SDL_StopTextInput();
						SDL_SetTextInputRect(&text);
						// SDL_StartTextInput();
						break;
					}
					if(e.window.event == SDL_WINDOWEVENT_FOCUS_LOST)
					{
						SDL_StopTextInput();
						break;
					}
					if(e.window.event != SDL_WINDOWEVENT_CLOSE)
							break;
					/* fallthrough */
				case SDL_QUIT:
					done = 1;
					break;
			}
		}
		t2 = SDL_GetTicks();
		if(t2 - t1 < cc)
			SDL_Delay(cc + t2 - t1);
	}
	SDL_FreeSurface(text_bg);
	for(i = 0; i != BTN_TOTAL;++i)
		btn_free((Btn *)b + i);
	SDL_DestroyTexture(tex);
	TTF_CloseFont(font);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);

	return;
testW_err:
	// SDL_Log("%s\n", SDL_GetError());
	if(text_s)
		SDL_FreeSurface(text_s);
	if(text_bg)
		SDL_FreeSurface(text_bg);
	if(font)
		TTF_CloseFont(font);
	if(tex)
		SDL_DestroyTexture(tex);
	if(ren)
		SDL_DestroyRenderer(ren);
	if(win)
		SDL_DestroyWindow(win);
}



