USE MINIASTRONOMY
GO

DELETE FROM LogTable
DELETE FROM MiniOBS
DELETE FROM MiniPlanets
DELETE FROM MiniResearchers

DBCC CHECKIDENT ('MiniPlanets', RESEED, 0);
DBCC CHECKIDENT ('MiniResearchers', RESEED, 0);
GO

INSERT INTO MiniPlanets(PName, PDensity, PPopulation) 
VALUES ('Mercury', 5.4, 0)
GO

CREATE OR ALTER PROC NonRepeatableRead1
AS
BEGIN
	BEGIN TRAN
	WAITFOR DELAY '00:00:05'
	UPDATE MiniPlanets SET PPopulation = 999
	WHERE PName = 'Mercury'
	COMMIT TRAN
END

EXEC NonRepeatableRead1
