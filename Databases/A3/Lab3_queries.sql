USE ASTRONOMY_DB
GO

-- a. modify column type ----------------------------------------------------------------------------
CREATE OR ALTER PROC uspModifyAsteroidDescriptionColumn
AS
	ALTER TABLE Asteroids
	ALTER COLUMN AsteroidDescription VARCHAR(50)
GO

CREATE OR ALTER PROC uspModifyRevertAsteroidDescriptionColumn
AS
	ALTER TABLE Asteroids
	ALTER COLUMN AsteroidDescription VARCHAR(30)
GO

-- b. add/drop column -------------------------------------------------------------------------------
CREATE OR ALTER PROC uspAddAsteroidSizeColumn
AS
	ALTER TABLE Asteroids
	ADD AsteroidSize INT
GO

CREATE OR ALTER PROC uspDropAsteroidSizeColumn
AS
	ALTER TABLE Asteroids
	DROP COLUMN AsteroidSize
GO

-- c. add/remove DEFAULT constraint ------------------------------------------------------------------
CREATE OR ALTER PROC uspAddDefaultConstraint
AS
	ALTER TABLE Asteroids
	ADD CONSTRAINT df_Description DEFAULT('potentially hazardous object') FOR AsteroidDescription
GO

CREATE OR ALTER PROC uspRemoveDefaultConstraint
AS
	ALTER TABLE Asteroids
	DROP CONSTRAINT df_Description
GO

-- d. add/remove primary key --------------------------------------------------------------------------
CREATE OR ALTER PROC uspAddPrimaryKey
AS
	ALTER TABLE Asteroids
	ADD CONSTRAINT pk_ID PRIMARY KEY (AsteroidID)
GO

CREATE OR ALTER PROC uspRemovePrimaryKey
AS
	ALTER TABLE Asteroids
	DROP CONSTRAINT pk_ID
GO

-- e. add/remove candidate key - make (Name, SSID) ----------------------------------------------------
CREATE OR ALTER PROC uspAddCandidateKey
AS
	ALTER TABLE Asteroids
	ADD CONSTRAINT ak_Name_SSID UNIQUE (AsteroidName, SSID)
GO

CREATE OR ALTER PROC uspRemoveCandidateKey
AS
	ALTER TABLE Asteroids
	DROP CONSTRAINT ak_Name_SSID
GO

-- f. add/remove foreign key ----------------------------------------------------------------------------
CREATE OR ALTER PROC uspAddForeignKey
AS
	ALTER TABLE Asteroids
	ADD CONSTRAINT fk_SSID FOREIGN KEY (SSID) REFERENCES SolarSystems(SSID)
GO

CREATE OR ALTER PROC uspRemoveForeignKey
AS
	ALTER TABLE Asteroids
	DROP CONSTRAINT fk_SSID
GO

-- g. create/drop a table ------------------------------------------------------------------------------
CREATE OR ALTER PROC uspCreateTableAsteroids
AS
	CREATE TABLE Asteroids(
		AsteroidID INT NOT NULL,
		AsteroidName VARCHAR(30),
		AsteroidDescription VARCHAR(30),
		SSID INT -- REFERENCES SolarSystems(SSID)
		)
GO

CREATE OR ALTER PROC uspDropTableAsteroids
AS
	DROP TABLE Asteroids
GO

-- get data in table -----------------------------------------------------------------------------------
CREATE OR ALTER PROC uspGetAsteroids
AS
	SELECT *
	FROM Asteroids
GO

--//////////////////////////////////////////////////////////////////////////////////////////////////////
/*
CREATE OR ALTER PROC uspSelectVersion @Version INT
AS
	DECLARE @SelectedVersion INT
	SET @SelectedVersion=
GO

avem i care takes crtVersion value
while i< (=) targetVersion
	set @SPName = (select ... from... where ...=@i)
	exec all uspUp until we reach them

while i> targetVersion
	exec all uspDown until we reach them

*/
CREATE OR ALTER PROC uspSelectVersion @NewVersion INT
AS
	DECLARE @currentVersion INT;
	DECLARE @SPName VARCHAR(60);
	--DECLARE @uspDown NVARCHAR(MAX);

	SET @currentVersion = (SELECT crtVersion from VersionTable)

	IF @NewVersion > 7 OR @NewVersion < 0
	BEGIN
	        RAISERROR ('Bad version', 10, 1)
			RETURN
	END

	WHILE @currentVersion > @NewVersion 
	BEGIN
		SET @SPName = (SELECT V.uspDown
					   FROM VersionSelector V
					   WHERE targetVersion = @currentVersion)
		PRINT(@SPName)
		EXEC(@SPName)
		SET @currentVersion=@currentVersion-1
		UPDATE VersionTable SET crtVersion=@currentVersion
	END

	WHILE @currentVersion < @NewVersion 
	BEGIN
		SET @SPName = (SELECT V.uspUp
					   FROM VersionSelector V
					   WHERE targetVersion = @currentVersion+1)
		PRINT(@SPName)
        EXEC(@SPName)
        SET @currentVersion=@currentVersion+1
		UPDATE VersionTable SET crtVersion=@currentVersion
    END

	--UPDATE VersionTable SET crtVersion=@NewVersion
	-- moved it in the while loop (in case it gets halfway to the version, then fails, update crtVersion!) 
	--execute uspSelectVersion 1
GO
CREATE OR ALTER PROC uspProcMain
AS
	EXEC uspDropTableAsteroids
	EXEC uspCreateTableAsteroids
	
	EXEC uspModifyAsteroidDescriptionColumn
	EXEC uspModifyRevertAsteroidDescriptionColumn

	EXEC uspAddAsteroidSizeColumn
	--EXEC uspDropAsteroidSizeColumn
	EXEC uspAddDefaultConstraint
	--EXEC uspRemoveDefaultConstraint
	EXEC uspAddPrimaryKey
	--EXEC uspRemovePrimaryKey
	EXEC uspAddCandidateKey
	--EXEC uspRemoveCandidateKey
	EXEC uspAddForeignKey
	--EXEC uspRemoveForeignKey

	--INSERT INTO Asteroids(AsteroidID,AsteroidName,SSID) VALUES (1,'name',1)
	EXEC uspGetAsteroids
GO
/*
-- CREATE TABLE CURRENT VERSION

SELECT * FROM VersionTable
DROP TABLE VersionSelector
CREATE TABLE VersionSelector(
	uspUp VARCHAR(50),
	uspDown VARCHAR(50),
	targetVersion INT PRIMARY KEY
	)
GO
INSERT INTO VersionSelector(uspUp, uspDown, targetVersion) VALUES('uspCreateTableAsteroids','uspDropTableAsteroids',1)
INSERT INTO VersionSelector(uspUp, uspDown, targetVersion) VALUES('uspModifyAsteroidDescriptionColumn','uspModifyRevertAsteroidDescriptionColumn',2)
INSERT INTO VersionSelector(uspUp, uspDown, targetVersion) VALUES('uspAddAsteroidSizeColumn','uspDropAsteroidSizeColumn',3)
INSERT INTO VersionSelector(uspUp, uspDown, targetVersion) VALUES('uspAddDefaultConstraint','uspRemoveDefaultConstraint',4)
INSERT INTO VersionSelector(uspUp, uspDown, targetVersion) VALUES('uspAddPrimaryKey','uspRemovePrimaryKey',5)
INSERT INTO VersionSelector(uspUp, uspDown, targetVersion) VALUES('uspAddCandidateKey','uspRemoveCandidateKey',6)
INSERT INTO VersionSelector(uspUp, uspDown, targetVersion) VALUES('uspAddForeignKey','uspRemoveForeignKey',7)
*/

--EXEC uspProcMain
SELECT * FROM VersionSelector
DROP TABLE VersionTable

CREATE TABLE VersionTable(
	crtVersion INT PRIMARY KEY
	)
INSERT INTO VersionTable(crtVersion) VALUES(0)  -- initial version
SELECT * FROM VersionTable
EXEC uspSelectVersion @NewVersion=0
SELECT* FROM Asteroids