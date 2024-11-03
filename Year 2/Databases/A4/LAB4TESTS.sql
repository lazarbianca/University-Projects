USE ASTRONOMY_DB
GO

-- insert the testName into TESTS
CREATE OR ALTER PROCEDURE addToTests @testName VARCHAR(100) 
AS
	IF EXISTS(SELECT* FROM Tests T WHERE Name = @testName)
	BEGIN
		RAISERROR('Test already exists in TESTS',10,1)
		RETURN
	END
	ELSE
		INSERT INTO Tests VALUES (@testName)

GO
-- insert the tableName into TABLES
CREATE OR ALTER PROCEDURE addToTables @tableName VARCHAR(100)
AS
	IF NOT EXISTS(SELECT * FROM sys.tables WHERE name=@tableName)
	BEGIN
		RAISERROR('Table does not exist in database',16,2)
		RETURN 
	END
	IF EXISTS(SELECT * FROM Tables T WHERE T.Name=@tableName)
	BEGIN
		RAISERROR('Table already exists in TABLES ',10,3)
		RETURN
	END
	INSERT INTO Tables(Name) VALUES (@tableName)


GO
-- insert entry to TestTables
CREATE OR ALTER PROCEDURE addToTestTables @tableName VARCHAR(100),@testName VARCHAR(100),@noOfRows INT,@position INT
AS
	IF @noOfRows<=0
	BEGIN
		RAISERROR('Number of rows should be greater than (>) zero',16,4)
		RETURN
	END
	IF @position<=0
	BEGIN
		RAISERROR('Position should be greater or equal (>=) to 1',16,5)
		RETURN
	END
	DECLARE @testID INT, @tableID INT
	-- from tableName and testName, get their IDs (in TABLES and TESTS) and add them into TestTables
	SET @testID=(SELECT T.TestID FROM Tests T WHERE T.Name=@testName)
	SET @tableID=(SELECT T.TableID FROM Tables T WHERE T.Name=@tableName)

	INSERT INTO TestTables(TestID,TableID,NoOfRows,Position) VALUES (@testID,@tableID,@noOfRows,@position)

GO
-- insert view to VIEWS
CREATE OR ALTER PROCEDURE addToViews @viewName VARCHAR(100)
AS
	IF NOT EXISTS(SELECT * FROM INFORMATION_SCHEMA.VIEWS WHERE TABLE_NAME=@viewName)
	BEGIN
		RAISERROR('View does not exist',16,6)
		RETURN
	END
	IF EXISTS(SELECT * FROM Views WHERE Name=@viewName)
	BEGIN
		RAISERROR('View already exists in VIEWS',16,7)
		RETURN
	END
	INSERT INTO Views(Name) VALUES (@viewName)

--insert entry to TestViews
GO 
CREATE OR ALTER PROCEDURE addToTestViews @viewName VARCHAR(100),@testName VARCHAR(100) 
AS
	DECLARE @testID INT,@viewID INT
	-- from viewName and testName, get their IDs (in VIEWS and TESTS) and add them into TestViews
	SET @testID=(SELECT TestID FROM Tests T WHERE T.Name=@testName)
	SET @viewID=(SELECT ViewID FROM Views V WHERE V.Name=@viewName)

	INSERT INTO TestViews(TestID,ViewID) VALUES (@testID,@viewID)

----------------------------------------------------------------------------------------------------------------------------
-- RUN TEST
GO
CREATE OR ALTER PROCEDURE uspRunTest @testName VARCHAR(100) 
AS
	DECLARE @TestID INT
	-- extract TESTS(testID) using TestName
    SET @TestID = (SELECT TestID FROM Tests WHERE Name = @TestName)

	-- insert TestRuns ( Description ) to be the current test name 
	DECLARE @testRunID INT
	INSERT INTO TestRuns(Description) VALUES(@testName)
	SET @testRunID=CONVERT(INT,(SELECT last_value FROM sys.identity_columns WHERE name='TestRunId'))

	------------------- TABLE CURSOR -------------------
    -- get all the TestTables(tableID)s and the corresponding NoOfRows that are part of the test (using testID)
    DECLARE TableCursor CURSOR SCROLL FOR --scroll to go forwards and backwards
    SELECT TableID, NoOfRows
    FROM TestTables
    WHERE TestID = @TestID
	ORDER BY Position  -- to figure out the order of deletes/inserts
	-- position will be the order for inserts !

	------------------- VIEW CURSOR --------------------
	-- SAME THING FOR VIEWS:
	DECLARE ViewCursor CURSOR SCROLL FOR
    SELECT ViewID
	FROM TestViews
    WHERE TestID = @TestID;

	DECLARE @globalStartTests DATETIME2, @globalEndTests DATETIME2;
	DECLARE @localStartTest DATETIME2, @localEndTest DATETIME2;
	
	SET @globalStartTests=SYSDATETIME();  ---------------------------------------GLOBAL START TIME------------------------
	
	DECLARE @noOfRows INT
	DECLARE @tableID INT
	DECLARE @viewID INT
	DECLARE @viewName VARCHAR(100)
    DECLARE @tableName VARCHAR(100)
	DECLARE @GenerateCommand VARCHAR(300)
	DECLARE @ViewRunCommand VARCHAR(300)

	OPEN TableCursor;
	FETCH FIRST FROM TableCursor INTO @tableID,@noOfRows
	WHILE @@FETCH_STATUS=0
	BEGIN
		SET @tableName = (SELECT Name FROM Tables WHERE TableID = @tableID)
		SET @localStartTest=SYSDATETIME(); -------------------------------------LOCAL START TIME TEST-----------------------
		-- populate the tables from the current test
		SET @GenerateCommand = 'generateRandomData ' + ''''+ @tableName + ''', '+ CAST(@noOfRows AS VARCHAR(10))
		EXEC(@GenerateCommand)
		-- done
		SET @localEndTest=SYSDATETIME(); --------------------------------------------------LOCAL END TIME TEST-----------------

		-- update TestRunTables with local start and end times
		INSERT INTO TestRunTables VALUES(@testRunID,@tableID,@localStartTest,@localEndTest)

		-- get next table that is part of the test
		FETCH NEXT FROM TableCursor INTO @tableID, @noOfRows

	END
	CLOSE TableCursor

	-- SAME PROCESS FOR VIEWS: ///////////////////////////////////////////////////////////////////////////////////////////////////
	OPEN ViewCursor
	FETCH FIRST FROM ViewCursor INTO @viewID
	WHILE @@FETCH_STATUS=0
	BEGIN
		SET @viewName = (SELECT Name FROM Views WHERE ViewID = @viewID)
		SET @localStartTest=SYSDATETIME(); -------------------------------------LOCAL START TIME TEST-----------------------
		-- run view
		SET @ViewRunCommand = 'SELECT * FROM ' + @viewName
		EXEC (@ViewRunCommand)
		-- done
		SET @localEndTest=SYSDATETIME(); --------------------------------------------------LOCAL END TIME TEST-----------------

		-- update TestRunViews with local start and end times
		INSERT INTO TestRunViews VALUES(@testRunID,@viewID,@localStartTest,@localEndTest)
		FETCH NEXT FROM ViewCursor INTO @viewID
	END
	CLOSE ViewCursor
	DEALLOCATE ViewCursor -- we no longer need it
	

	-- go backwards for deleting from the table
	-- shouldnt this be above everything?
	OPEN TableCursor
	FETCH LAST FROM TableCursor INTO @tableID, @noOfRows

	WHILE @@FETCH_STATUS=0
	BEGIN
		SET @tableName = (SELECT Name FROM Tables WHERE TableID = @tableID)
		EXEC DeleteTable @tableName 
		FETCH PRIOR FROM TableCursor INTO @tableID, @noOfRows
	END
	CLOSE TableCursor
	DEALLOCATE TableCursor

	SET @globalEndTests = SYSDATETIME();  ---------------------------------------GLOBAL END TIME------------------------
	
	-- update TestRuns with the global start and end times
	UPDATE TestRuns
	SET StartAt=@globalStartTests, EndAt=@globalEndTests
	WHERE TestRunID=@testRunID
GO

SELECT * FROM Views
SELECT * FROM Tables
SELECT * FROM TestViews
SELECT * FROM Tests
SELECT * FROM TestTables 
SELECT * FROM TestRunTables
SELECT * FROM TestRuns
SELECT * FROM TestRunViews

DELETE FROM TestRuns
DELETE FROM TestRunTables
DELETE FROM TestRunViews
DELETE FROM TestViews
DELETE FROM TestTables 
DELETE FROM Views
DELETE FROM Tables
DELETE FROM Tests

-- Test 1 - 3 tables
EXEC addToTests 'Test1'
EXEC addToTables 'Planets'
EXEC addToTables 'Researchers'
EXEC addToTables 'Observe'
EXEC addToTestTables 'Planets', 'Test1', 1000, 1
EXEC addToTestTables 'Researchers', 'Test1', 1000, 2
EXEC addToTestTables 'Observe', 'Test1', 100, 3
EXEC uspRunTest 'Test1'

SELECT * FROM TestRunTables
SELECT * FROM TestRuns

-- Test 2 - 3 tables, 1 views
EXEC addToTests 'Test2'
EXEC addToTables 'Planets'
EXEC addToTables 'Researchers'
EXEC addToTables 'Observe'
EXEC addToTestTables 'Planets', 'Test2', 1000, 1
EXEC addToTestTables 'Researchers', 'Test2', 1000, 2
EXEC addToTestTables 'Observe', 'Test2', 100, 3
EXEC addToViews 'vResearchersMoreThan2Obs'
EXEC addToTestViews 'vResearchersMoreThan2Obs', 'Test2'
EXEC uspRunTest 'Test2'

SELECT * FROM TestRunTables
SELECT * FROM TestRunViews
SELECT * FROM TestRuns

-- Test 3
EXEC addToTests 'Test3'
EXEC addToTables 'Planets'
EXEC addToTables 'Researchers'
EXEC addToTables 'Observe'
EXEC addToTestTables 'Planets', 'Test3', 1000, 1
EXEC addToTestTables 'Researchers', 'Test3', 1000, 2
EXEC addToTestTables 'Observe', 'Test3', 100, 3
EXEC addToViews 'vGetDataIfPopulation'
EXEC addToTestViews 'vGetDataIfPopulation', 'Test3'
EXEC uspRunTest 'Test3'

SELECT * FROM TestRunTables
SELECT * FROM TestRunViews
SELECT * FROM TestRuns