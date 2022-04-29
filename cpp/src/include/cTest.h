#ifndef _C_TEST_H__
#define _C_TEST_H__

#define MACRO_PACKED __attribute__((packed));

#ifdef __cplusplus
extern "C"
{
#endif
	int cTest1();
	int cppTest1();
#ifdef __cplusplus
}
#endif



#ifdef __cplusplus
namespace cppTest
{
	class Message
	{
		private:
			std::string message;
		public:
			Message();
			Message(std::string s);
			void show() const;
			std::string getMessage() const;
			friend std::ostream& operator<<(std::ostream&, const Message&);
	};
};

#endif

#endif
