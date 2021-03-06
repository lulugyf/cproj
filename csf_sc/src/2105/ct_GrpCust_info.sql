DROP TABLE  CT_GRPCUST_INFO CASCADE CONSTRAINTS;

CREATE TABLE  CT_GRPCUST_INFO
(
  CUST_ID             NUMBER(14)                NOT NULL,
  UNIT_ID             NUMBER(10)                NOT NULL,
  GROUP_TYPE          NUMBER(4)                 NOT NULL,
  SCOPE_CODE          NUMBER(4)                 NOT NULL,
  TRADE_CODE          VARCHAR2(8 BYTE)          NOT NULL,
  LEAVE_DATE          DATE,
  CREDIT_GRADE        CHAR(1 BYTE),
  TRADE_DETAIL        VARCHAR2(20 BYTE),
  ENT_TYPE            NUMBER(4)                 NOT NULL,
  ENT_CODE            VARCHAR2(60 BYTE),
  AREA_TYPE           NUMBER(4)                 NOT NULL,
  FAX                 VARCHAR2(60 BYTE),
  UNIT_HOMEPAGE       VARCHAR2(60 BYTE),
  UNIT_LEADER         VARCHAR2(60 BYTE),
  MANAGE_AREA         VARCHAR2(512 BYTE),
  REGISTER_ADDRESS    VARCHAR2(100 BYTE),
  REGISTER_BANKROLL   VARCHAR2(100 BYTE),
  YEAR_TURNOVER       VARCHAR2(100 BYTE),
  YEAR_GAIN           VARCHAR2(100 BYTE),
  TOP_DEPUTY_NAME     VARCHAR2(100 BYTE),
  TOP_DEPUTY_PHONE    VARCHAR2(20 BYTE),
  UNIT_CREATE_DAY     DATE,
  LICENSE_NUMBER      VARCHAR2(30 BYTE),
  SIGN_DATE           DATE,
  LICENSE_VALIDATE    VARCHAR2(20 BYTE),
  INSTITUTION_TYPE    VARCHAR2(10 BYTE),
  BANK_NAME           VARCHAR2(60 BYTE),
  BANK_ACCOUNT_NO     VARCHAR2(30 BYTE),
  VALID_FLAG          VARCHAR2(5 BYTE),
  REVOKE_DATE         DATE,
  INFORMATION_FLAG    CHAR(2 BYTE),
  NATIONAL_UNIT_CODE  VARCHAR2(20 BYTE),
  UNIT_PAY_NO         VARCHAR2(30 BYTE),
  UNIT_PHOTO          VARCHAR2(1 BYTE),
  UNIT_SIGN           VARCHAR2(128 BYTE),
  EMAIL_ADDRESS       VARCHAR2(60 BYTE),
  GROUP_HQ_NAME       VARCHAR2(255 BYTE),
  OPERATOR_PHONE      VARCHAR2(30 BYTE),
  STATUS_CODE         CHAR(1 BYTE),
  FINISH_FLAG         CHAR(1 BYTE)              NOT NULL,
  OP_TIME             DATE                      NOT NULL,
  LOGIN_ACCEPT        NUMBER(18)                NOT NULL,
  LOGIN_NO            VARCHAR2(20 BYTE)         NOT NULL,
  OP_CODE             CHAR(5 BYTE)              NOT NULL,
  NOTE                VARCHAR2(255 BYTE),
  PRODUCT_TYPE        VARCHAR2(8 BYTE)
);


CREATE INDEX  IDX_CT_GRPCUST_INFO ON  CT_GRPCUST_INFO
(UNIT_ID);


CREATE INDEX  IDX_LCT_GRPCUST_INFO ON  CT_GRPCUST_INFO
(LICENSE_NUMBER);


CREATE UNIQUE INDEX  PK_CT_GRPCUST_INFO ON  CT_GRPCUST_INFO
(CUST_ID);


CREATE INDEX  PK_GRPCUST_INFO ON  CT_GRPCUST_INFO
(LOGIN_ACCEPT);


DROP PUBLIC SYNONYM CT_GRPCUST_INFO;

CREATE PUBLIC SYNONYM CT_GRPCUST_INFO FOR  CT_GRPCUST_INFO;

-------------------------------------------------------------------------------------------

DROP TABLE  CT_GRPCUST_INFO_HIS CASCADE CONSTRAINTS;

CREATE TABLE  CT_GRPCUST_INFO_HIS
(
  CUST_ID             NUMBER(14)                NOT NULL,
  UNIT_ID             NUMBER(10)                NOT NULL,
  GROUP_TYPE          NUMBER(4),
  SCOPE_CODE          NUMBER(4),
  TRADE_CODE          VARCHAR2(8 BYTE),
  LEAVE_DATE          DATE,
  CREDIT_GRADE        CHAR(1 BYTE),
  TRADE_DETAIL        VARCHAR2(20 BYTE),
  ENT_TYPE            NUMBER(4),
  ENT_CODE            VARCHAR2(60 BYTE),
  AREA_TYPE           NUMBER(4),
  FAX                 VARCHAR2(60 BYTE),
  UNIT_HOMEPAGE       VARCHAR2(60 BYTE),
  UNIT_LEADER         VARCHAR2(60 BYTE),
  MANAGE_AREA         VARCHAR2(512 BYTE),
  REGISTER_ADDRESS    VARCHAR2(100 BYTE),
  REGISTER_BANKROLL   VARCHAR2(100 BYTE),
  YEAR_TURNOVER       VARCHAR2(100 BYTE),
  YEAR_GAIN           VARCHAR2(100 BYTE),
  TOP_DEPUTY_NAME     VARCHAR2(100 BYTE),
  TOP_DEPUTY_PHONE    VARCHAR2(20 BYTE),
  UNIT_CREATE_DAY     DATE,
  LICENSE_NUMBER      VARCHAR2(30 BYTE),
  SIGN_DATE           DATE,
  LICENSE_VALIDATE    VARCHAR2(20 BYTE),
  INSTITUTION_TYPE    VARCHAR2(10 BYTE),
  BANK_NAME           VARCHAR2(60 BYTE),
  BANK_ACCOUNT_NO     VARCHAR2(30 BYTE),
  VALID_FLAG          VARCHAR2(5 BYTE),
  REVOKE_DATE         DATE,
  INFORMATION_FLAG    CHAR(2 BYTE),
  NATIONAL_UNIT_CODE  VARCHAR2(20 BYTE),
  UNIT_PAY_NO         VARCHAR2(30 BYTE),
  UNIT_PHOTO          VARCHAR2(1 BYTE),
  UNIT_SIGN           VARCHAR2(128 BYTE),
  EMAIL_ADDRESS       VARCHAR2(60 BYTE),
  GROUP_HQ_NAME       VARCHAR2(255 BYTE),
  OPERATOR_PHONE      VARCHAR2(30 BYTE),
  STATUS_CODE         CHAR(1 BYTE),
  FINISH_FLAG         CHAR(1 BYTE)              NOT NULL,
  OP_TIME             DATE                      NOT NULL,
  LOGIN_ACCEPT        NUMBER(18)                NOT NULL,
  LOGIN_NO            VARCHAR2(20 BYTE)         NOT NULL,
  OP_CODE             CHAR(5 BYTE)              NOT NULL,
  NOTE                VARCHAR2(255 BYTE),
  UPDATE_ACCEPT       NUMBER(18)                NOT NULL,
  UPDATE_TIME         DATE                      NOT NULL,
  UPDATE_DATE         NUMBER(8)                 NOT NULL,
  UPDATE_LOGIN        VARCHAR2(20 BYTE)         NOT NULL,
  UPDATE_TYPE         CHAR(1 BYTE)              NOT NULL,
  UPDATE_CODE         CHAR(5 BYTE)              NOT NULL,
  PRODUCT_TYPE        VARCHAR2(8 BYTE)
);


CREATE UNIQUE INDEX  PK_CT_GRPCUST_INFO_HIS ON  CT_GRPCUST_INFO_HIS
(CUST_ID, UPDATE_ACCEPT, UPDATE_TYPE);


DROP PUBLIC SYNONYM CT_GRPCUST_INFO_HIS;

CREATE PUBLIC SYNONYM CT_GRPCUST_INFO_HIS FOR  CT_GRPCUST_INFO_HIS;

