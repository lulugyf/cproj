#include <framework.h>

class multi_db_connect{
	private:
		DCI_SQL dsql;
		DCI* pdci;
		otl_connect* potl;
		DCI dci;
		otl_connect otl;
		time_t lastConn;
		time_t lastTry;
		bool isMainConn;
		string mainName;
		string mainUser;
		string mainPass;
		string mainType;
		string bakName;
		string bakUser;
		string bakPass;
		string bakType;
		string lable;
		bool hasInitPrepare;
		bool isActive;
		bool stuff();
	public:
		void init(const char* lab);

		void setActive(bool is);
		bool getActive();
		time_t getLastConnectTime();
		multi_db_connect(const char* lab);
		multi_db_connect();
		const char* getCurType();
		const char* getConnectLable();
		otl_connect& getOtlHandle();
		DCI& getMDBHandle();
		void doConnect();

		void doClose();
		bool tryConnect();
		void doCommit();
		void doRollback();
		~multi_db_connect();
};


typedef void* (*work_f)(void* v1, multi_db_connect* pdb, bool isLong);
class multi_db_factory{
	private:
		map<string, multi_db_connect*> dbmap;
		map<string, bool> maskmap;
		bool isLong;
	public:
		multi_db_factory(bool is);
		multi_db_factory();
		multi_db_connect* getConnect(const char* lable);
		void setShortLong(bool is);
		void addConnect(const char* lable, bool isWork);
		void setActive(const char* lablestr);
		void resetActive();
		multi_db_connect* addConnect(const char* lablestr);
		bool doBegin();


		void doCall(map<string, void*>& m, work_f func, void* v1);
		void doEnd(bool isCommit);
		~multi_db_factory();
};
