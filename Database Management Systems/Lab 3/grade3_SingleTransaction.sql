USE MINIASTRONOMY
GO

-- GRADE 3: SINGLE TRANSACTION --

CREATE OR ALTER PROCEDURE InsertMiniPlanetAndResearchers
    @PName VARCHAR(30),
    @PDensity FLOAT,
    @PPopulation INT,
    @RName VARCHAR(30),
    @RDoB DATE,
    @RDepartment VARCHAR(30),
    @DoOBS DATETIME,
    @Obs VARCHAR(80)
AS
BEGIN
    SET XACT_ABORT ON;
    BEGIN TRANSACTION;

    BEGIN TRY
		-- Validations
		IF @PName = '' OR @PName IS NULL
        BEGIN
            RAISERROR('Invalid Planet Name', 16, 1);
        END
        IF @PDensity <= 0
        BEGIN
            RAISERROR('Invalid Planet Density', 16, 1);
        END
        IF @PPopulation < 0
        BEGIN
            RAISERROR('Invalid Planet Population', 16, 1);
        END
        IF @RName = '' OR @RName IS NULL
        BEGIN
            RAISERROR('Invalid Researcher Name', 16, 1);
        END
        IF @RDepartment = '' OR @RDepartment IS NULL
        BEGIN
            RAISERROR('Invalid Researcher Department', 16, 1);
        END
        IF @DoOBS < '1900-01-01'
        BEGIN
            RAISERROR('Invalid Observation Date', 16, 1);
        END

        DECLARE @PID INT, @RID INT;

        -- Insert into MiniPlanets
        INSERT INTO MiniPlanets (PName, PDensity, PPopulation)
        VALUES (@PName, @PDensity, @PPopulation);
        SET @PID = SCOPE_IDENTITY();

        -- Insert into MiniResearchers
        INSERT INTO MiniResearchers (RName, RDoB, RDepartment)
        VALUES (@RName, @RDoB, @RDepartment);
        SET @RID = SCOPE_IDENTITY();

        -- Insert into MiniOBS
        INSERT INTO MiniOBS (PID, RID, DoOBS, Obs)
        VALUES (@PID, @RID, @DoOBS, @Obs);

        -- Log operations
        INSERT INTO LogTable (TypeOperation, TableOperation, ExecutionDate)
        VALUES ('INSERT', 'MiniPlanets', GETDATE());
        INSERT INTO LogTable (TypeOperation, TableOperation, ExecutionDate)
        VALUES ('INSERT', 'MiniResearchers', GETDATE());
        INSERT INTO LogTable (TypeOperation, TableOperation, ExecutionDate)
        VALUES ('INSERT', 'MiniOBS', GETDATE());

        COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        ROLLBACK TRANSACTION;

        -- Log the error
        INSERT INTO LogTable (TypeOperation, TableOperation, ExecutionDate)
        VALUES ('ERROR', 'InsertMiniPlanetAndResearchers', GETDATE());
        THROW;
    END CATCH
END


-- happy scenario
-- Test 1: Successful insert into all tables
EXEC InsertMiniPlanetAndResearchers
    @PName = 'PlanetA',
    @PDensity = 5.5,
    @PPopulation = 1000000,
    @RName = 'John Doe',
    @RDoB = '1980-01-01',
    @RDepartment = 'Astrophysics',
    @DoOBS = '2024-05-22 10:00:00',
    @Obs = 'Observation of PlanetA';
    
-- Verify the inserts
SELECT * FROM MiniPlanets WHERE PName = 'PlanetA';
SELECT * FROM MiniResearchers WHERE RName = 'John Doe';
SELECT * FROM MiniOBS WHERE Obs = 'Observation of PlanetA';

SELECT * FROM LogTable

-- bad scenario
-- Test 2: Fail to insert into MiniResearchers (name too long) and expect rollback
EXEC InsertMiniPlanetAndResearchers
    @PName = '', -- INVALID NAME
    @PDensity = 0,
    @PPopulation = 300000,
    @RName = 'Bob Johnson',
    @RDoB = '1990-11-11',
    @RDepartment = 'Meteorology',
    @DoOBS = '2024-05-23 12:00:00',
    @Obs = 'Observation of PlanetD';
    
-- Verify the inserts: No rows should be added due to rollback
SELECT * FROM MiniPlanets WHERE PName = 'PlanetD';
SELECT * FROM MiniResearchers WHERE RName = 'Bob Johnson';
SELECT * FROM MiniOBS WHERE Obs = 'Observation of PlanetD';

SELECT * FROM LogTable
