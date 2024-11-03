USE MINIASTRONOMY
GO

DELETE FROM LogTable
DELETE FROM MiniOBS
DELETE FROM MiniPlanets
DELETE FROM MiniResearchers

DBCC CHECKIDENT ('MiniPlanets', RESEED, 0);
DBCC CHECKIDENT ('MiniResearchers', RESEED, 0);

GO

INSERT INTO MiniPlanets(PName, PDensity, PPopulation) VALUES 
('Mercury', 5.4, 0),
('Venus', 5.2, 0)

INSERT INTO MiniResearchers(RName, RDoB, RDepartment) VALUES 
('John Smith', '1990-01-01', 'Astrophysics'),
('Jane Doe', '1985-06-15', 'Planetary Science')

GO
CREATE OR ALTER PROC Deadlock1
AS
BEGIN
	BEGIN TRAN
	UPDATE MiniPlanets SET PName = 'Deadlock1 Planet' WHERE PID=1
	-- this transaction has exclusively lock on table MiniPlanets
	WAITFOR DELAY '00:00:10'
	UPDATE MiniResearchers SET RName='Deadlock1 Researcher' WHERE RID=1
	-- this transaction will be blocked because transaction 2 has already
	-- blocked our lock on table MiniResearchers
	COMMIT TRAN
END

GO

EXEC Deadlock1

SELECT * FROM MiniPlanets
SELECT * FROM MiniResearchers
