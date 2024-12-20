USE MINIASTRONOMY
GO

DELETE FROM LogTable
DELETE FROM MiniOBS
DELETE FROM MiniPlanets
DELETE FROM MiniResearchers

DBCC CHECKIDENT ('MiniPlanets', RESEED, 0);
DBCC CHECKIDENT ('MiniResearchers', RESEED, 0);

GO
CREATE OR ALTER PROC PhantomRead1
AS
BEGIN
	BEGIN TRAN
	WAITFOR DELAY '00:00:04'
	INSERT INTO MiniPlanets(PName, PDensity, PPopulation) 
	VALUES ('Phantom Planet', 5.4, 0)
	COMMIT TRAN
END

GO
EXEC PhantomRead1