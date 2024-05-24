USE MINIASTRONOMY
GO

-- GRADE 5: PARTIAL SUCCESS --

CREATE OR ALTER PROCEDURE InsertMiniPlanetAndResearchersPartial
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
    SET NOCOUNT ON;
	DECLARE @PID INT, @RID INT;
    begin try
        BEGIN TRANSACTION;
		IF @PName = '' OR @PName IS NULL
		BEGIN
            RAISERROR('Invalid Planet Name', 16, 1);
			RETURN;
		END
		IF @PDensity <= 0
        BEGIN
			RAISERROR('Invalid Planet Density', 16, 1);
			RETURN;
		END
		IF @PPopulation < 0
        BEGIN
			RAISERROR('Invalid Planet Population', 16, 1);
			RETURN;
		END

		-- Insert into MiniPlanets
        INSERT INTO MiniPlanets (PName, PDensity, PPopulation)
        VALUES (@PName, @PDensity, @PPopulation);
		SET @PID = SCOPE_IDENTITY();
		INSERT INTO LogTable (TypeOperation, TableOperation, ExecutionDate)
        VALUES ('INSERT', 'MiniPlanet Insert', GETDATE());
		COMMIT TRANSACTION;
	end try
	BEGIN CATCH
        IF @@TRANCOUNT > 0
            ROLLBACK TRANSACTION;

		INSERT INTO LogTable (TypeOperation, TableOperation, ExecutionDate)
        VALUES ('ERROR', 'MiniPlanet Insert', GETDATE());
        -- Raise error
        DECLARE @ErrorMessage NVARCHAR(4000) = ERROR_MESSAGE();
        RAISERROR(@ErrorMessage, 16, 1);
    END CATCH;
	begin try
		BEGIN TRANSACTION;
		-- Validate inputs for MiniResearchers
        IF @RName = '' OR @RName IS NULL
		BEGIN
            RAISERROR('Invalid Researcher Name', 16, 1);
			RETURN;
		END
		IF @RDepartment = '' OR @RDepartment IS NULL
		BEGIN
            RAISERROR('Invalid Researcher Department', 16, 1);
			RETURN;
		END

		INSERT INTO MiniResearchers (RName, RDoB, RDepartment)
        VALUES (@RName, @RDoB, @RDepartment);
		SET @RID = SCOPE_IDENTITY();
		INSERT INTO LogTable (TypeOperation, TableOperation, ExecutionDate)
        VALUES ('INSERT', 'MiniResearchers Insert', GETDATE());
		COMMIT TRANSACTION;
	end try
	BEGIN CATCH
        IF @@TRANCOUNT > 0
            ROLLBACK TRANSACTION;
		INSERT INTO LogTable (TypeOperation, TableOperation, ExecutionDate)
        VALUES ('ERROR', 'MiniResearchers Insert', GETDATE());
        RAISERROR(@ErrorMessage, 16, 1);
    END CATCH;
	begin try
		BEGIN TRANSACTION;
		IF @DoOBS < '1900-01-01'
		BEGIN
            RAISERROR('Invalid Observation Date', 16, 1);
			RETURN;
		END

        -- Insert into MiniOBS
        INSERT INTO MiniOBS (PID, RID, DoOBS, Obs)
        VALUES (@PID, @RID, @DoOBS, @Obs);

		INSERT INTO LogTable (TypeOperation, TableOperation, ExecutionDate)
        VALUES ('INSERT', 'MiniOBS Insert', GETDATE());
        COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        IF @@TRANCOUNT > 0
            ROLLBACK TRANSACTION;
		INSERT INTO LogTable (TypeOperation, TableOperation, ExecutionDate)
        VALUES ('ERROR', 'MiniOBS Insert', GETDATE());
        RAISERROR(@ErrorMessage, 16, 1);
    END CATCH;
END;

-- happy scenario
EXEC InsertMiniPlanetAndResearchersPartial
    @PName = 'PlanetPartialA',
    @PDensity = 5.5,
    @PPopulation = 1000000,
    @RName = 'John Doe',
    @RDoB = '1980-01-01',
    @RDepartment = 'Astrophysics',
    @DoOBS = '2024-05-22 10:00:00',
    @Obs = 'Observation of PlanetPartialA';

-- Verify the inserts
SELECT * FROM MiniPlanets;
SELECT * FROM MiniResearchers;
SELECT * FROM MiniOBS;

SELECT * FROM LogTable

-- error scenarios
-- Empty Planet Name
-- Test Scenario: Invalid Planet Name
EXEC InsertMiniPlanetAndResearchersPartial
    @PName = '',               -- Invalid planet name
    @PDensity = 5.67,
    @PPopulation = 10000,
    @RName = 'John Doe',
    @RDoB = '1990-05-15',
    @RDepartment = 'Research Department',
    @DoOBS = '2024-05-23',
    @Obs = 'Observation Text';


-- Verify the inserts
SELECT * FROM MiniPlanets;
SELECT * FROM MiniResearchers;
SELECT * FROM MiniOBS;

SELECT * FROM LogTable

EXEC InsertMiniPlanetAndResearchersPartial
    @PName = 'PlanetPartialA',
    @PDensity = 5.5,
    @PPopulation = 1000000,
    @RName = '',
    @RDoB = '1980-01-01',
    @RDepartment = 'Astrophysics',
    @DoOBS = '2024-05-22 10:00:00',
    @Obs = 'Observation of PlanetPartialA';

-- Verify the inserts
SELECT * FROM MiniPlanets;
SELECT * FROM MiniResearchers;
SELECT * FROM MiniOBS;

SELECT * FROM LogTable