
USE FTPDB;
GO

DROP TABLE IF EXISTS FileSystemTree;
GO
DROP TABLE IF EXISTS Hosts;
GO
DROP PROCEDURE IF EXISTS UpdateItemComment;
GO
DROP PROCEDURE IF EXISTS SyncDirectories;
GO
DROP PROCEDURE IF EXISTS AuthenticateHost;
GO
DROP TYPE IF EXISTS DirectoryShortcut;
GO


CREATE TABLE Hosts
	(
		HostID INT IDENTITY NOT NULL PRIMARY KEY, 
		HostAddress VARCHAR(30)
	);
GO

CREATE TABLE FileSystemTree	
	(
		ItemID INT IDENTITY NOT NULL PRIMARY KEY, 
		ItemName VARCHAR(100),
		ItemComment VARCHAR(300),
		DirectoryID INT FOREIGN KEY REFERENCES FileSystemTree(ItemID),
		HostID INT NOT NULL FOREIGN KEY REFERENCES Hosts(HostID)
	);
GO

CREATE TYPE DirectoryShortcut AS TABLE ( 
	ItemName VARCHAR(100) NOT NULL PRIMARY KEY
)
GO


CREATE PROCEDURE dbo.AuthenticateHost
	@HostName VARCHAR(30)
AS
	DECLARE @IsNewHost BIT;
	SET @IsNewHost = 
		(
			SELECT CAST(COUNT(HostAddress) AS BIT) FROM Hosts
			WHERE HostAddress = @HostName
		);

	IF @IsNewHost = 0
	BEGIN
		INSERT INTO Hosts (HostAddress)
		SELECT @HostName;
	END

	DECLARE @HostID INT;
	SELECT @HostID = HostID
	FROM Hosts 
	WHERE HostAddress = @HostName;

	IF @IsNewHost = 0
	BEGIN
		INSERT FileSystemTree(ItemName, ItemComment, DirectoryID, HostID)
		VALUES ('root', NULL, NULL, @HostID);
	END 

	SELECT @HostID;
GO


CREATE PROCEDURE SyncDirectories
	@HostID INT,
	@DirectoryID INT,
	@Directory DirectoryShortcut READONLY
AS
	MERGE FileSystemTree AS T
	USING @Directory AS S
	ON (T.HostID = @HostID AND T.DirectoryID = @DirectoryID AND T.ItemName = S.ItemName)
	WHEN NOT MATCHED BY TARGET
		THEN INSERT(ItemName, ItemComment, DirectoryID, HostID)
			VALUES(S.ItemName, NULL, @DirectoryID, @HostID)
	WHEN NOT MATCHED BY SOURCE AND T.DirectoryID = @DirectoryID AND T.HostID = @HostID 
		THEN DELETE;

	SELECT ItemID, ItemName, ItemComment
	FROM FileSystemTree
	WHERE HostID = @HostID AND DirectoryID = @DirectoryID;
GO


CREATE PROCEDURE UpdateItemComment
	@HostID INT,
	@ItemID INT,
	@ItemComment VARCHAR(300)
AS
	UPDATE FileSystemTree 
	SET ItemComment = @ItemComment	
	WHERE HostID = @HostID AND ItemID = @ItemID; 
GO


---------------------------------------------------------------------------


SELECT * FROM FileSystemTree;
SELECT * FROM Hosts;


---------------------------------------------------------------------------