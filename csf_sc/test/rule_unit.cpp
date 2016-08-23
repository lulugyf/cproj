#include <framework.h>

extern "C" utype * pRQUserOweFeeFunc(const utype* puInParam, TCtrlInfo* errInfo)
{
	LOG_FUNC_BP();
	L4C_TRACE("---------pRQUserOweFeeFunc begin-------------------");
	uAutoPtr uBusiInfo(uInit(0));
	uAutoPtr uView(uInit(1));
	uAutoPtr uAccountInfo(uInit(0));
	uAutoPtr outView(uInit(0));
	uAutoPtr outUser(uInit(0));
	uAutoPtr outParam(uInit(0));
    char sTOTAL_CURRENT_OWED_FEE[20+1];
    char sTOTAL_UNCHARGED_SUM[20+1];
    char sTOTAL_OWE_FEE_SUM[20+1];

	uBusiInfo=utClone(utGetStructByDir(puInParam,"IN_DATA","REQUEST_INFO","BUSI_INFO_LIST","BUSI_INFO"));



	if(utFind(uBusiInfo,"ID_NO")!=-1)
	{
		outUser = cQUserInfoByIdNo(uBusiInfo,errInfo);
		if (0 == outUser->cnt )
		{
			throw(appException(406001019, "û�и��û�����Ϣ"));
		}
	}
	else if(utFind(uBusiInfo,"PHONE_NO")!=-1)
	{
		outUser = cQUserInfoByMasPhone(uBusiInfo,errInfo);
		if (0 == outUser->cnt )
		{
			throw(appException(406001019, "û�и��û�����Ϣ"));
		}
	}else
	{
		throw(appException(406001027, "�봫����֤����[ID_NO��PHONE_NO]"));
	}



	L4C_TRACE("hello,here--------���ù�����ѯ");
	uAutoPtr uUserOweFee(uInit(1));
	utAddLong(uUserOweFee,"CONTRACT_NO",utGetLong(outUser,"CONTRACT_NO"));
	utAddLong(uUserOweFee,"ID_NO",utGetLong(outUser,"ID_NO"));
	outView = pubQueryUserOweFee(uUserOweFee,errInfo);

	memset(sTOTAL_CURRENT_OWED_FEE,0,sizeof(sTOTAL_CURRENT_OWED_FEE));
	memset(sTOTAL_UNCHARGED_SUM,0,sizeof(sTOTAL_UNCHARGED_SUM));
	memset(sTOTAL_OWE_FEE_SUM,0,sizeof(sTOTAL_OWE_FEE_SUM));

	if (0 == outView->cnt )         //�޷��������û���쳣������Ĭ�����������֤���쳣
	{
		utAddDouble(outParam,"TOTAL_CURRENT_OWED_FEE",0.00);
		utAddDouble(outParam,"TOTAL_UNCHARGED_SUM",0.00);
		utAddDouble(outParam,"TOTAL_OWE_FEE_SUM",0.00);
	}else//ת����Ԫ���
	{
		utAddDouble(outParam,"TOTAL_CURRENT_OWED_FEE",utGetDouble(outView,"TOTAL_CURRENT_OWED_FEE")/100);//����Ƿ��
		utAddDouble(outParam,"TOTAL_UNCHARGED_SUM",utGetDouble(outView,"TOTAL_UNCHARGED_SUM")/100);     //����Ƿ��
		utAddDouble(outParam,"TOTAL_OWE_FEE_SUM",utGetDouble(outView,"TOTAL_OWE_FEE_SUM")/100); //��Ƿ��
	}

	L4C_TRACE("---------pRQUserOweFeeFunc end------------------ -");
	return outParam.release();
}
