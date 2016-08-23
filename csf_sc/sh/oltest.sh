#生成订单走flow_code=3的流程
clxml sOrderTst "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>
<Root>
        <REQUEST_INFO type=\"node\">
                <BUSIINFO_LIST type=\"node\">
                        <ORDER_INFO type=\"node\">
                                <BUSI_TYPE_ID type=\"long\">1</BUSI_TYPE_ID>
                                <CUST_ID_TYPE type=\"int\">2</CUST_ID_TYPE>
                                <SERVICE_NO type=\"string\">13955100001</SERVICE_NO>
                        </ORDER_INFO>
                        <BUSIINFO type=\"node\">
                                <BUSI_MODEL type=\"node\">
                                        <OPTR_FLAG type=\"string\">1</OPTR_FLAG>
                                        <LMT_ADJUST_TYPE type=\"string\">10</LMT_ADJUST_TYPE>
                                        <LIMIT_OWE type=\"double\">4.677</LIMIT_OWE>
                                </BUSI_MODEL>
                                <BUSI_BATCH>
                                        <RECORD_LIST>
                                                <RECORD>
                                                        <BRAND_ID type=\"string\">002</BRAND_ID>
                                                        <ID_NO type=\"long\">11080278100050</ID_NO>
                                                </RECORD>
                                        </RECORD_LIST>
                                        <RECORD_PATH>
                                        </RECORD_PATH>
                                </BUSI_BATCH>
                                <ORDER_LINE_FEELIST>
                                </ORDER_LINE_FEELIST>
                                <SERVICE_OFFER_ID type=\"long\">9999</SERVICE_OFFER_ID>
                                <SERIAL_NO type=\"long\">1</SERIAL_NO>
                                <CUST_ID_TYPE type=\"int\">2</CUST_ID_TYPE>
                                <DOC_SEQ  type=\"long\">1</DOC_SEQ>
                        </BUSIINFO>

                </BUSIINFO_LIST>
                <OPR_INFO type=\"node\">
                        <CHANNEL_TYPE type=\"string\">3</CHANNEL_TYPE>
                        <CUST_ID_TYPE type=\"int\">2</CUST_ID_TYPE>
                        <OP_CODE type=\"string\">9999</OP_CODE>
                        <GROUP_ID type=\"string\">10011</GROUP_ID>
                        <SERVICE_NO type=\"string\">13955100001</SERVICE_NO>
                        <LOGIN_PWD type=\"string\">CODCDOJHGECIFONG</LOGIN_PWD>
                        <OP_NOTE type=\"string\">text</OP_NOTE>
                        <CONTACT_ID type=\"string\">55000000005901</CONTACT_ID>
                        <REGION_ID type=\"int\">11</REGION_ID>
                        <ID_NO type=\"long\">11080278100050</ID_NO>
                        <SYS_NOTE type=\"string\">text</SYS_NOTE>
                        <CUST_ID type=\"long\">22080268043298</CUST_ID>
                        <LOGIN_NO type=\"string\">aaaa01</LOGIN_NO>
                        <CONTRACT_NO type=\"long\">22080268043300</CONTRACT_NO>
                        <IP_ADDRESS type=\"string\">172.16.9.13</IP_ADDRESS>
                        <BRAND_ID type=\"string\">001</BRAND_ID>
                        <!--MASTER_SERV_ID type=\"string\">1204</MASTER_SERV_ID-->
                </OPR_INFO>
        </REQUEST_INFO>
        <MSG_TYPE type=\"node\">
                <BATCH_TYPE type=\"int\">1</BATCH_TYPE>
                <TEMPLATE_ID type=\"long\">1</TEMPLATE_ID>
                <AUTO_CONFIRM type=\"string\">N</AUTO_CONFIRM>
        </MSG_TYPE>
</Root>"
