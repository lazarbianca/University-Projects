USE ASTRONOMY_DB
GO
--dbcc check ident reseed
DBCC CHECKIDENT ('Galaxies', RESEED, 999);
DBCC CHECKIDENT ('SolarSystems', RESEED, 0);
DBCC CHECKIDENT ('Planets', RESEED, 99);
DBCC CHECKIDENT ('Researchers', RESEED, 0);
DBCC CHECKIDENT ('Astronauts', RESEED, 0);
DBCC CHECKIDENT ('Satellites', RESEED, 109);
DBCC CHECKIDENT ('Stars', RESEED, 119);
-- OBS! for the first run, we start from 999; for second execute, we start with 1000
GO
DELETE
FROM Explore

DELETE
FROM Astronauts

DELETE
FROM Satellites

DELETE
FROM Observe

DELETE
FROM Planets

DELETE
FROM SolarSystems

DELETE
FROM Galaxies

DELETE
FROM Researchers

INSERT INTO Galaxies(GName) VALUES ('Milky Way') --id from 999
INSERT INTO Galaxies(GName) VALUES ('Andromeda')
INSERT INTO Galaxies(GName) VALUES ('Pinwheel Galaxy')

INSERT INTO SolarSystems(SSName,GID) VALUES ('Solar System 1',1000) --id from 0
INSERT INTO SolarSystems(SSName,GID) VALUES ('Solar System 2',1000)
INSERT INTO SolarSystems(SSName,GID) VALUES ('Solar System 3',1000)

INSERT INTO Planets(PName,PDensity,PPopulation,SSID) VALUES ('Earth',7888000000,5515,1) --id from 99
--INSERT INTO Planets(PName,PDensity,PPopulation,SSID) VALUES ('Mars',5243000000,0,3) --Referential violation 
INSERT INTO Planets(PName,PDensity,PPopulation,SSID) VALUES ('Mars',5243000000,0,3)
INSERT INTO Planets(PName,PDensity,PPopulation,SSID) VALUES ('Venus',5243000000,0,1)

--researchers
INSERT INTO Researchers(RName,RDepartment,RDoB) VALUES('r1','chemistry','1987-10-10') --id from 0
INSERT INTO Researchers(RName,RDepartment,RDoB) VALUES('r2','physics','1990-12-30')
INSERT INTO Researchers(RName,RDepartment,RDoB) VALUES('r3','chemistry','1973-03-17')
INSERT INTO Researchers(RName,RDepartment,RDoB) VALUES('r4','rocket science','1969-09-20')

--observe
INSERT INTO Observe(PID,RID,DoOBS,OBS) VALUES('100','1','2019-10-12','inconclusive')
INSERT INTO Observe(PID,RID,DoOBS,OBS) VALUES('100','1','2020-11-02','observation 2')
INSERT INTO Observe(PID,RID,DoOBS,OBS) VALUES('102','1','2020-10-12','inconclusive')
INSERT INTO Observe(PID,RID,DoOBS,OBS) VALUES('101','2','1999-10-12','inconclusive')
INSERT INTO Observe(PID,RID,DoOBS,OBS) VALUES('101','2','1998-10-12','very conclusive')
INSERT INTO Observe(PID,RID,DoOBS,OBS) VALUES('102','3','2023-10-12','observation 2.2')

INSERT INTO Satellites(SatName, PID) VALUES('sat1','100')  --id from 109
INSERT INTO Satellites(SatName, PID) VALUES('sat2','100')
INSERT INTO Satellites(SatName, PID) VALUES('sat3','101')
INSERT INTO Satellites(SatName, PID) VALUES('sat4','101')
INSERT INTO Satellites(SatName, PID) VALUES('sat5','102')


INSERT INTO Astronauts(AName, ADoB) VALUES('a1','1950-06-18')  --id from 0
INSERT INTO Astronauts(AName, ADoB) VALUES('a2','1982-06-13')
INSERT INTO Astronauts(AName, ADoB) VALUES('a3','1979-04-23')

INSERT INTO Explore(AstronautID, SatID, DoEXP,EXPConclusion,EXPDuration) VALUES('1','110','1999-06-01','inconclusive',48)
INSERT INTO Explore(AstronautID, SatID, DoEXP,EXPConclusion,EXPDuration) VALUES('1','112','2004-02-01','big and cold',72)
INSERT INTO Explore(AstronautID, SatID, DoEXP,EXPConclusion,EXPDuration) VALUES('3','113','2014-06-01','very nice',104)

INSERT INTO Stars(StarName, Constellation, SSID) VALUES('star1', 'constellation1',1)
INSERT INTO Stars(StarName, Constellation, SSID) VALUES('star2', 'constellation1',1)
INSERT INTO Stars(StarName, Constellation, SSID) VALUES('star3', 'constellation1',1)
INSERT INTO Stars(StarName, Constellation, SSID) VALUES('star4', 'constellation2',3)

INSERT INTO IsVisible(StarID, PlanetID, Distance) VALUES('120','100',789876)
INSERT INTO IsVisible(StarID, PlanetID, Distance) VALUES('121','100',676767)

--SELECT *
--FROM Researchers

--SELECT *
--FROM Planets

--SELECT *
--FROM Observe

SELECT *
FROM Satellites

SELECT *
FROM Astronauts
--SELECT *

SELECT *
FROM Explore
--FROM Galaxies

--SELECT * 
--FROM SolarSystems