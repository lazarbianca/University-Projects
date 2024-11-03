USE MINIASTRONOMY
GO

-- ONLY THE ROW IS LOCKED; IF WE EXECUTE WITH ID=2 IT WILL NOT CAUSE DEADLOCK
CREATE OR ALTER PROC Deadlock2
AS
BEGIN
	SET DEADLOCK_PRIORITY HIGH
	BEGIN TRAN
	UPDATE MiniResearchers SET RName='Deadlock2 Researcher' WHERE RID=1
	-- this transaction has exclusively lock on table MiniResearchers
	WAITFOR DELAY '00:00:10'
	UPDATE MiniPlanets SET PName = 'Deadlock2 Planet' WHERE PID=1
	-- this transaction will be blocked because transaction 1 has 
	-- exclusive lock on THE ROW IN table MiniPlanets, so, both of the transactions 
	-- are blocked
	COMMIT TRAN
	-- after some seconds transaction 2 will be chosen as a deadlock victim and terminates with an error
	-- in tables MiniPlanets and MiniResearchers will be the values from transaction 1
END


EXEC Deadlock2

GO
CREATE OR ALTER PROC DeadlockSolution
AS
BEGIN
	BEGIN TRAN
	UPDATE MiniPlanets SET PName = 'Deadlock2 Planet' WHERE PID=1
	WAITFOR DELAY '00:00:10'
	UPDATE MiniResearchers SET RName='Deadlock2 Researcher' WHERE RID=1
	COMMIT TRAN
END
GO

EXEC DeadlockSolution