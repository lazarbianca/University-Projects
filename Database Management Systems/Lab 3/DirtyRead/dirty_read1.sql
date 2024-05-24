USE MINIASTRONOMY
GO

INSERT INTO MiniPlanets (PName, PDensity, PPopulation) VALUES
('Mercury', 5.4, 0),
('Venus', 5.2, 0),
('Earth', 5.5, 79000000)
GO

DELETE FROM LogTable
DELETE FROM MiniOBS
DELETE FROM MiniPlanets
DELETE FROM MiniResearchers

DBCC CHECKIDENT ('MiniPlanets', RESEED, 0);
DBCC CHECKIDENT ('MiniResearchers', RESEED, 0);
GO

-- Dirty read: Reading uncommitted data that might be rolled back.
CREATE OR ALTER PROC DirtyRead1
AS
BEGIN
	BEGIN TRANSACTION
	UPDATE MiniPlanets SET PName = 'Dirty Name'
	WHERE PID = 1
	WAITFOR DELAY '00:00:10'
	ROLLBACK TRANSACTION
END

GO

EXEC DirtyRead1

SELECT * FROM MiniPlanets