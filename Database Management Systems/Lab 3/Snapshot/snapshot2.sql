USE MINIASTRONOMY
GO

CREATE OR ALTER PROC Snapshot2
AS
BEGIN
	SET TRANSACTION ISOLATION LEVEL SNAPSHOT
	BEGIN TRAN
	SELECT * FROM MiniPlanets WHERE PID=1
	WAITFOR DELAY '00:00:10'
	SELECT * FROM MiniPlanets WHERE PID=2
	UPDATE MiniPlanets SET PName = 'Snapshot2 Planet' WHERE PID=1
	-- process will block
	-- Process will receive Error 3960.
	COMMIT TRAN
END

GO
EXEC Snapshot2