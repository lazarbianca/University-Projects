USE ASTRONOMY_DB
GO

CREATE OR ALTER PROCEDURE generateRandomInt @intValue INT OUTPUT
AS
	SET @intValue = FLOOR(RAND() * 1000) + 100
GO

CREATE OR ALTER PROCEDURE generateRandomBigInt @bigIntValue BIGINT OUTPUT
AS
	SET @bigIntValue = FLOOR(RAND() * 10000) + 1000
GO
--procedure to generate a random string with a limited length
CREATE OR ALTER PROCEDURE generateRandomString @stringValue VARCHAR(10) OUTPUT 
AS
	DECLARE @length INT
	DECLARE @charPool VARCHAR(55)
	DECLARE @charPoolLength INT
	SET @charPool = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ'
	SET @charPoolLength = LEN(@charPool)
	SET @length = FLOOR(RAND() * 10 + 5)
	SET @stringValue = ''
	WHILE @length > 0
	BEGIN
		SET @stringValue = @stringValue + SUBSTRING(@charPool, CONVERT(INT, RAND() * @charPoolLength) + 1, 1)
		SET @length = @length - 1
	END
GO

-- generate random data for a table
CREATE OR ALTER PROC generateRandomData @tableName VARCHAR(100), @nrOfRows INT
AS
	-- extract table schema using TableName and sys.objects
	DECLARE @SchemaQuery NVARCHAR(MAX)
    SET @SchemaQuery = N'
        SELECT
            COLUMN_NAME,
            DATA_TYPE,
            COLUMNPROPERTY(OBJECT_ID(TABLE_SCHEMA + ''.'' + TABLE_NAME), COLUMN_NAME, ''IsIdentity'') AS IS_IDENTITY
        FROM
            INFORMATION_SCHEMA.COLUMNS C
        WHERE
            TABLE_NAME = N''' + @TableName + '''';
	--PRINT 'SchemaQuery : ' + @SchemaQuery
    -- execute the schema query
    DECLARE @ColumnName NVARCHAR(MAX);
    DECLARE @DataType NVARCHAR(MAX);
	DECLARE @IsIdentity BIT;
	DECLARE @IsPrimaryKey BIT;
	DECLARE @IsForeignKey BIT;
	DECLARE @hasPK INT;
	-- checkIfPKQuery 
	DECLARE @checkIfPKQuery NVARCHAR(2000);
	DECLARE @outputPK INT;
    -- to avoid global cursors:
    -- create a temporary table to store the result of the dynamic SQL
    CREATE TABLE #TempSchemaTable (
        COLUMN_NAME NVARCHAR(MAX),
        DATA_TYPE NVARCHAR(MAX),
        IS_IDENTITY BIT
    );

    -- execute the schema query and insert results into the temporary table
    INSERT INTO #TempSchemaTable
    EXEC sp_executesql @SchemaQuery;

    -- declare a cursor on the temporary table; cursors can only be declared on selects
    DECLARE SchemaCursor SCROLL CURSOR FOR
    SELECT COLUMN_NAME, DATA_TYPE, IS_IDENTITY FROM #TempSchemaTable;

    -- iterate over the column name, data type, and schema flags from the @TableName's schema
    OPEN SchemaCursor;
	
	-- sql identity does not behave as expected; collect values and insert once, at the end
	DECLARE @ValuesList NVARCHAR(MAX)
	DECLARE @ColumnsList NVARCHAR(MAX)
	SET @ValuesList = '('
	SET @ColumnsList = '('

	--while loop for generating as long as < nrOfRows
	DECLARE @Counter INT = 0;

	WHILE @Counter < @nrOfRows
	BEGIN
		-- reset values and columns for each row
		SET @ValuesList = '('
		SET @ColumnsList = '('
		Print 'Entered while loop, counter = '+ CAST(@Counter AS VARCHAR(10)) + ' and nrOfRows = ' + CAST(@nrOfRows AS VARCHAR(19))
		FETCH FIRST FROM SchemaCursor INTO @ColumnName, @DataType, @IsIdentity;
		PRINT @ColumnName + ' '+@DataType +' '+CAST(@IsIdentity  AS VARCHAR(MAX))

		-- generate and insert random data based on the schema
		-- we will build the insert query, depending on what we have to insert
		DECLARE @InsertQuery NVARCHAR(MAX);
		
		WHILE @@FETCH_STATUS = 0
		BEGIN
			-- generate random data based on data type
			DECLARE @RandomString NVARCHAR(MAX);
			DECLARE @RandomInt INT;
			DECLARE @RandomBigInt BIGINT;
			DECLARE @RandomBigIntSTRING NVARCHAR(MAX)
			DECLARE @RandomDate DATE;
			DECLARE @RandomDateTime DATETIME;

			-- if column is not identity, we add values
			IF @IsIdentity = 0
			BEGIN
				-- check if it is a FK
				-- check if the current column has a foreign key property and if it has, take its values from the referenced table
				IF EXISTS(
					SELECT *
					FROM INFORMATION_SCHEMA.CONSTRAINT_COLUMN_USAGE C
					WHERE C.CONSTRAINT_NAME like 'FK%' AND @columnName = C.COLUMN_NAME AND @tableName = C.TABLE_NAME)
					BEGIN
						-- get the name of the referenced table and the name of the referenced column
						DECLARE @referencedTable VARCHAR(50)
						DECLARE @referencedColumn VARCHAR(50)
						DECLARE @result TABLE([tableName] VARCHAR(50), [columnName] VARCHAR(50))
						INSERT INTO @result SELECT OBJECT_NAME (f.referenced_object_id) AS referenced_table_name,
						COL_NAME(fc.referenced_object_id, fc.referenced_column_id) AS referenced_column_name
						FROM sys.foreign_keys AS f
						INNER JOIN sys.foreign_key_columns AS fc ON f.object_id = fc.constraint_object_id
						WHERE fc.parent_object_id = OBJECT_ID(@tableName) AND COL_NAME(fc.parent_object_id, fc.parent_column_id) = @columnName

						SET @referencedTable = (SELECT TOP 1 [tableName] FROM @result)
						SET @referencedColumn = (SELECT TOP 1 [columnName] FROM @result)
						
						-- empty the table, otherwise it will always have at the top the first table and column found
						DELETE FROM @result
						
						-- generate:
						IF @DataType = 'int'
								BEGIN
									PRINT 'int FK Generation'
									-- get a random value from the referenced table
									DECLARE @RandomFKQuery NVARCHAR(1000)
									SET @RandomFKQuery = N'SELECT TOP 1 @RandomInt = [' + @referencedColumn + '] FROM ' + @referencedTable + ' ORDER BY NEWID()'
									PRINT '!!!!!!!!!!!!!!!!!!!!!!!! Now testing: ' + @RandomFKQuery
									EXEC sp_executesql @RandomFKQuery, N'@RandomInt INT OUTPUT', @RandomInt OUTPUT
									
									SET @ColumnsList = @ColumnsList + @ColumnName + ','
									SET @ValuesList = @ValuesList +CAST(@RandomInt AS VARCHAR(10))+','
									PRINT @ColumnsList + '     ' + @ValuesList
								END
					END
				ELSE -- not a FK
					BEGIN
					IF @DataType = 'varchar'
							BEGIN
								EXEC generateRandomString @stringValue=@RandomString OUTPUT
								PRINT 'not FK; generating random string:'+@RandomString
								SET @ColumnsList = @ColumnsList + @ColumnName + ','
								SET @ValuesList = @ValuesList + ''''+@RandomString+''','
								PRINT @ColumnsList + '     ' + @ValuesList

							END
					ELSE
						IF @DataType = 'int'
								BEGIN
									EXEC generateRandomInt @intValue = @RandomInt OUTPUT
									PRINT 'not FK; generating random int:' +CAST(@RandomInt AS VARCHAR(10))
									SET @ColumnsList = @ColumnsList + @ColumnName + ','
									SET @ValuesList = @ValuesList +CAST(@RandomInt AS VARCHAR(10))+','
									PRINT @ColumnsList + '     ' + @ValuesList
								
								END
						ELSE
							IF @DataType = 'bigint'
								BEGIN
									EXEC generateRandomBigInt @bigIntValue = @RandomBigInt OUTPUT
									SET @RandomBigIntSTRING = CAST(@RandomBigInt AS VARCHAR(19))
									PRINT 'not FK; generating random bigInt: ' + @RandomBigIntSTRING
									
									SET @ColumnsList = @ColumnsList + @ColumnName + ','
									SET @ValuesList = @ValuesList +CAST(@RandomBigInt AS VARCHAR(19))+','
									PRINT @ColumnsList + '     ' + @ValuesList
								
								END
							ELSE
								IF @DataType = 'datetime'
									BEGIN
										SET  @RandomDateTime = GETDATE()
										PRINT 'not FK; generating random DATE TIME: ' + CONVERT(NVARCHAR(19), @RandomDateTime, 120)

										SET @ColumnsList = @ColumnsList + @ColumnName + ','
										SET @ValuesList = @ValuesList +''''+CONVERT(NVARCHAR(19), @RandomDateTime, 120)+''','
										PRINT @ColumnsList + '     ' + @ValuesList
									END
								ELSE
									IF @DataType = 'date'
										BEGIN
											SET @RandomDate = CONVERT(DATE, GETDATE());
											PRINT 'not FK; generating random DATE: ' + CONVERT(NVARCHAR(10), @RandomDate, 120)

											SET @ColumnsList = @ColumnsList + @ColumnName + ','
											SET @ValuesList = @ValuesList + ''''+CONVERT(NVARCHAR(10), @RandomDate, 120)+''','
											PRINT @ColumnsList + '     ' + @ValuesList
										
										END
									ELSE
										BEGIN
										PRINT 'HERE HERE HERE HERE ! Insert NULL on '+ @ColumnName

										SET @ColumnsList = @ColumnsList + @ColumnName + ','
										SET @ValuesList = @ValuesList +NULL+','
										PRINT @ColumnsList + '     ' + @ValuesList
										
										END
					END
			END	
			PRINT 'currently, ' + @ColumnsList + ' and ' + @ValuesList
			FETCH NEXT FROM SchemaCursor INTO @ColumnName, @DataType, @IsIdentity;
			PRINT 'moving on to = ' + @ColumnName + ' '+@DataType +' '+CAST(@IsIdentity AS VARCHAR(MAX))
		END
		-- All primary key values are unique (id is always unique -identity), proceed with the insert
		-- Remove the last character (extra comma)
		SET @ColumnsList = LEFT(@ColumnsList, LEN(@ColumnsList) - 1)
		SET @ValuesList = LEFT(@ValuesList, LEN(@ValuesList) - 1)
		SET @InsertQuery = 'INSERT INTO ' + @TableName + ' ' + @ColumnsList + ') VALUES ' + @ValuesList + ')';
										
		PRINT 'Insert Query = ' + @insertQuery
		EXEC (@insertQuery)
		SET @Counter = @Counter + 1;
		PRINT 'counter = '+ CAST(@Counter as varchar(10))
	END
    -- close and deallocate the cursor on the temporary table
    CLOSE SchemaCursor;
    DEALLOCATE SchemaCursor;

    -- drop the temporary table
    DROP TABLE #TempSchemaTable;
-- end generate random data

--procedure for deleting from tables
GO
CREATE OR ALTER PROCEDURE DeleteTable @tableName VARCHAR(50)
AS
	EXEC('DELETE FROM '+@tableName)

GO
-- VIEWS ----------------------------------------------------------------------------------------------------------
CREATE OR ALTER VIEW vResearchersMoreThan2Obs
AS
	-- Researchers with more than 2 observations
	SELECT O.RID
	FROM Observe O
	GROUP BY RID
	HAVING COUNT(*) > 2

GO
CREATE OR ALTER VIEW vGetDataIfPopulation
AS
	-- Get data about researchers, observations(ALL- date of obs differs) and planets, where planet population>0
	SELECT *
	FROM Researchers R FULL JOIN Observe O ON R.ResearcherID=O.RID FULL JOIN Planets P ON O.PID=P.PlanetID
	WHERE P.PPopulation>0

GO
CREATE OR ALTER VIEW vGetSatellitesOrbitPopulatedPlanets
AS
	-- find all satellites which orbit populated planets
	SELECT *
	FROM Satellites S
	WHERE EXISTS (
				SELECT *
				FROM Planets P
				WHERE P.PPopulation>0 AND S.PID=P.PlanetID
				)

GO

EXEC DeleteTable 'Observe'
EXEC DeleteTable 'Planets'
EXEC DeleteTable 'Researchers'
EXEC generateRandomData 'Researchers', 10
EXEC generateRandomData 'Planets', 10
EXEC generateRandomData 'Observe',10

SELECT * FROM Planets
SELECT * FROM Observe
SELECT * FROM Researchers
SELECT * FROM vResearchersMoreThan2Obs