
-- Table: User table

CREATE TABLE Users (
	UserID INTEGER PRIMARY KEY,  -- 主键
	UserName TEXT,				 -- 用户名
	PassWord VARCHAR,			 -- 用户登录密码
	Description TEXT,			 -- 用户描述信息
	UserEmail TEXT,				 -- 用户关联邮箱，用于找回密码
	UserPhoneNumber NUMERIC,	 -- 用户手机号码，用于密码找回
	other	 TEXT     			 -- 其他信息
	
);

-- Table: Accounts 保存用户其他平台注册的账号
CREATE TABLE Accounts (
	AccountID NUMERIC PRIMARY KEY,  				-- 用户id
	UserID INTEGER	  REFERENCES Users ( UserID ), 	-- foreigner key
	AccountName VARCHAR,  							-- 账户名称
	AccountPwd   VARCHAR,  							-- 用户密码
	AccountEmail TEXT,  							-- 用户关联的邮箱
	AccountPhoneNumber NUMERIC, 					-- phone number
	other TEXT
);
	
	