USE MINIASTRONOMY
GO
DROP TABLE MiniOBS
DROP TABLE MiniPlanets
DROP TABLE MiniResearchers
DROP TABLE LogTable
GO

CREATE TABLE MiniPlanets (
	PID INT IDENTITY PRIMARY KEY,
	PName VARCHAR(30),
	PDensity FLOAT,
	PPopulation INT
)

CREATE TABLE MiniResearchers(
	RID INT IDENTITY PRIMARY KEY,
	RName VARCHAR(30),
	RDoB DATE,
	RDepartment VARCHAR(30)
)

CREATE TABLE MiniOBS(
	PID INT REFERENCES MiniPlanets(PID),
	RID INT REFERENCES MiniResearchers(RID),
	DoOBS DATETIME,
	Obs VARCHAR(80),
	CONSTRAINT PK_MiniOBS PRIMARY KEY (PID, RID, DoOBS)
)

GO

INSERT INTO MiniPlanets (PName, PDensity, PPopulation) VALUES
('Mercury', 5.4, 0),
('Venus', 5.2, 0),
('Earth', 5.5, 79000000),
('Mars', 3.9, 0),
('Jupiter', 1.3, 0);

INSERT INTO MiniResearchers (RName, RDoB, RDepartment) VALUES
('John Smith', '1990-01-01', 'Astrophysics'),
('Jane Doe', '1985-06-15', 'Planetary Science'),
('Bob Johnson', '1992-03-20', 'Biology'),
('Alice Brown', '1980-11-12', 'Geology'),
('Mike Davis', '1995-08-25', 'Astrophysics');

INSERT INTO MiniOBS (PID, RID, DoOBS, Obs) VALUES
(1, 1, '2022-01-01 10:00:00', 'Observed unusual asteroid activity near Mercury'),
(2, 1, '2022-01-05 14:00:00', 'Detected unusual radiation patterns on Venus'),
(3, 1, '2022-02-10 08:00:00', 'Collected samples of Martian soil'),
(4, 4, '2022-03-15 12:00:00', 'Observed unusual planetary rotation of Jupiter'),
(5, 5, '2022-04-20 16:00:00', 'Detected signs of water presence on Mars'),
(1, 1, '2022-06-01 11:00:00', 'Follow-up observation of asteroid activity near Mercury');

GO

SELECT * FROM MiniPlanets
SELECT * FROM MiniResearchers
SELECT * FROM MiniOBS
SELECT * FROM LogTable
GO

CREATE TABLE LogTable(
	Lid INT IDENTITY PRIMARY KEY,
	TypeOperation VARCHAR(50),
	TableOperation VARCHAR(50),
	ExecutionDate DATETIME
)

GO

DELETE FROM LogTable
DELETE FROM MiniOBS
DELETE FROM MiniPlanets
DELETE FROM MiniResearchers

DBCC CHECKIDENT ('MiniPlanets', RESEED, 0);
DBCC CHECKIDENT ('MiniResearchers', RESEED, 0);
