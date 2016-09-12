CREATE TABLE CAT_CONTRACT_ACTION(
   ID   		INT              NOT NULL		AUTO_INCREMENT,
   CONTRACT_ID 	INT     		 NOT NULL,
   ACTION  		VARCHAR (50),
   COMMENTS		VARCHAR (2000),
   STATUS		VARCHAR (50),
   CREATED_DATE DATE			 NOT NULL,
   UPDATED_DATE DATE			 NOT NULL,
   CREATED_BY	VARCHAR (50)	 NOT NULL,
   UPDATED_BY	VARCHAR (50)	 NOT NULL,
   DELETED_FLAG	VARCHAR (1),
   PRIMARY KEY (ID)
);