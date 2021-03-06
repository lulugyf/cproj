DROP TABLE  CT_CUSTSPECIALLIST_INFO CASCADE CONSTRAINTS;

CREATE TABLE  CT_CUSTSPECIALLIST_INFO
(
  CUST_ID        NUMBER(14)                     NOT NULL,
  LIST_TYPE      VARCHAR2(4 BYTE)               NOT NULL,
  OP_CODE        VARCHAR2(4 BYTE)               NOT NULL,
  OP_TIME        DATE                           NOT NULL,
  LOGIN_NO       VARCHAR2(20 BYTE)              NOT NULL,
  LOGIN_ACCEPT   NUMBER(18)                     NOT NULL,
  EFF_DATE       DATE,
  EXP_DATE       DATE,
  FINISH_FLAG    CHAR(1 BYTE),
  REGISTOR_NAME  VARCHAR2(60 BYTE),
  REMARK         VARCHAR2(255 BYTE),
  GROUP_ID       VARCHAR2(10 BYTE)
);


CREATE UNIQUE INDEX  PK_CT_CUSTSPECIALLIST_INFO ON  CT_CUSTSPECIALLIST_INFO
(CUST_ID, LIST_TYPE);


CREATE INDEX  PK_CUSTSPECIALLIST_INFO ON  CT_CUSTSPECIALLIST_INFO
(LOGIN_ACCEPT);


DROP PUBLIC SYNONYM CT_CUSTSPECIALLIST_INFO;

CREATE PUBLIC SYNONYM CT_CUSTSPECIALLIST_INFO FOR  CT_CUSTSPECIALLIST_INFO;

---------------------------------------------------------------------------------------------------------

DROP TABLE  CT_CUSTSPECIALLIST_INFO_HIS CASCADE CONSTRAINTS;

CREATE TABLE  CT_CUSTSPECIALLIST_INFO_HIS
(
  CUST_ID        NUMBER(14)                     NOT NULL,
  LIST_TYPE      VARCHAR2(4 BYTE)               NOT NULL,
  OP_CODE        VARCHAR2(4 BYTE)               NOT NULL,
  OP_TIME        DATE                           NOT NULL,
  LOGIN_NO       VARCHAR2(20 BYTE)              NOT NULL,
  LOGIN_ACCEPT   NUMBER(18)                     NOT NULL,
  EFF_DATE       DATE,
  EXP_DATE       DATE,
  FINISH_FLAG    CHAR(1 BYTE),
  REGISTOR_NAME  VARCHAR2(60 BYTE),
  REMARK         VARCHAR2(255 BYTE),
  GROUP_ID       VARCHAR2(10 BYTE),
  UPDATE_ACCEPT  NUMBER(18)                     NOT NULL,
  UPDATE_TIME    DATE                           NOT NULL,
  UPDATE_DATE    NUMBER(8)                      NOT NULL,
  UPDATE_LOGIN   VARCHAR2(20 BYTE)              NOT NULL,
  UPDATE_TYPE    CHAR(1 BYTE)                   NOT NULL,
  UPDATE_CODE    CHAR(5 BYTE)                   NOT NULL
);


CREATE UNIQUE INDEX  PK_CT_CUSTSPECIALLIST_INFO_HIS ON  CT_CUSTSPECIALLIST_INFO_HIS
(CUST_ID, LIST_TYPE, UPDATE_ACCEPT, UPDATE_TYPE);


DROP PUBLIC SYNONYM CT_CUSTSPECIALLIST_INFO_HIS;

CREATE PUBLIC SYNONYM CT_CUSTSPECIALLIST_INFO_HIS FOR  CT_CUSTSPECIALLIST_INFO_HIS;

