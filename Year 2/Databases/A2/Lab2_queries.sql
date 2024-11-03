USE ASTRONOMY_DB
GO

SELECT *
FROM Observe
-----------------------------------------------------------------------------------------
--		a. UNION [ALL] and OR
-- for UNION, we must have the same column count in both queries
-- UNION ALL keeps duplicates, UNION does not

--Find researcher IDs who are in 'chemistry' department OR have more than 2 observations 
-- Researchers in 'chemistry' department
SELECT R.ResearcherID
FROM Researchers R
WHERE RDepartment = 'chemistry'
UNION ALL
-- Researchers with more than 2 observations
SELECT O.RID
FROM Observe O
GROUP BY RID
HAVING COUNT(*) > 2

-- Returns rows that meet at least one of these conditions
SELECT *
FROM Researchers R
WHERE RDepartment = 'chemistry' OR R.RDepartment ='rocket science'

-----------------------------------------------------------------------------------------
--		b. INTERSECT and IN
--Return Researcher IDs that have BOTH the department 'chemistry' AND inconclusive observation
-- Researchers in 'chemistry' department
SELECT R.ResearcherID
FROM Researchers R
WHERE R.RDepartment='chemistry'
INTERSECT
-- Researchers with 'inconclusive' observations
SELECT O.RID
FROM Observe O
WHERE O.Obs = 'inconclusive'

-- Researcher info with inconclusive observations (Duplicates removed)
SELECT *
FROM Researchers R
WHERE R.ResearcherID IN
	(
	-- The Researcher Ids with inconclusive observations
	SELECT O.RID
	FROM Observe O
	WHERE O.Obs='inconclusive'
	)

-- Researcher AND Observe data with inconclusive observations (Duplicates allowed)
SELECT *
FROM Researchers R INNER JOIN Observe O ON R.ResearcherID=O.RID
WHERE O.Obs='inconclusive'

-----------------------------------------------------------------------------------------
--		c. EXCEPT and NOT IN
-- Researcher IDs with 'chemistry' department, BUT NOT inconclusive operations
-- Researchers in 'chemistry' department
SELECT R.ResearcherID
FROM Researchers R
WHERE R.RDepartment='chemistry'
EXCEPT
-- Researchers with 'inconclusive' observations
SELECT O.RID
FROM Observe O
WHERE O.Obs = 'inconclusive'

-- Researcher info with 'chemistry' department BUT NOT inconclusive observations
SELECT *
FROM Researchers R
WHERE R.RDepartment='chemistry' AND R.ResearcherID NOT IN
	(
	-- The Researcher Ids with inconclusive observations
	SELECT O.RID
	FROM Observe O
	WHERE O.Obs='inconclusive'
	)

-----------------------------------------------------------------------------------------
--		d. INNER JOIN, LEFT JOIN, RIGHT JOIN, FULL JOIN
-- join 3 tables:
-- Get data about researchers, observations(ALL- date of obs differs) and planets, where planet population>0
SELECT *
FROM Researchers R FULL JOIN Observe O ON R.ResearcherID=O.RID FULL JOIN Planets P ON O.PID=P.PlanetID
WHERE P.PPopulation>0

SELECT *
FROM Planets P FULL JOIN Observe O ON P.PlanetID=O.PID FULL JOIN IsVisible V ON P.PlanetID=V.PlanetID RIGHT JOIN Stars S ON S.StarID=V.StarID
WHERE P.PPopulation>0 AND O.Obs='inconclusive'

SELECT *
FROM Stars S LEFT JOIN IsVisible V ON S.StarID=V.StarID

SELECT *
FROM Stars S RIGHT JOIN IsVisible V ON S.StarID=V.StarID

-----------------------------------------------------------------------------------------
--		e. WHERE ... IN (  ... WHERE( ...)  ) (+1 b)
-- Astronaut info of the astronauts with those IDs
SELECT *
FROM Astronauts A
WHERE A.AstronautID IN
	( -- Astronauts which have explored those satellites
	SELECT E.AstronautID
	FROM Explore E
	WHERE E.SatID IN
		( -- Satellites which orbit those planets
		SELECT S.SatID
		FROM Satellites S
		WHERE S.PID IN 
			( -- Planets with population > 0
			SELECT P.PlanetID
			FROM Planets P
			WHERE P.PPopulation>0
			)
		)
	)

-----------------------------------------------------------------------------------------
--		f. WHERE EXISTS ( ... )
-- find the researchers who have at least an observation marked inconclusive (removes duplicates)
SELECT *
FROM Researchers R
WHERE EXISTS(
			SELECT *
			FROM Observe O
			WHERE O.Obs='inconclusive' AND R.ResearcherID=O.RID
			)

-- find all satellites which orbit populated planets
SELECT *
FROM Satellites S
WHERE EXISTS (
			SELECT *
			FROM Planets P
			WHERE P.PPopulation>0 AND S.PID=P.PlanetID
			)

-----------------------------------------------------------------------------------------
--		g. FROM ( ... )
--find youngest researcher (name and id) per observed planet
SELECT t.PID, t.minAGE, R.ResearcherID, R.RName
FROM Researchers R INNER JOIN (
	SELECT O.PID, MAX(R.RDoB) minAGE
	FROM Researchers R INNER JOIN Observe O ON R.ResearcherID = O.RID
		INNER JOIN Planets P ON O.PID = P.PlanetID
	GROUP BY O.PID) t
ON R.RDoB=t.minAGE
GO

--returns rName, rID and nr of observations a researcher made (in total)
SELECT R.RName, t.RID, t.NrObs
FROM Researchers R INNER JOIN
	( --Returns the RID and NrObs for each researcher with MORE THAN 1 observation
	SELECT O.RID, COUNT(*) NrObs
	FROM Observe O
	GROUP BY O.RID
	HAVING COUNT(*)>1) t
ON t.RID = R.ResearcherID

--//
-- Names of Researchers who have (at least one) Observations on Planets 
--that are orbitted by at least a Satellite that has been 
--Explored PRIOR to its Exploration
--
-- For each Planet that an Observation has been done on, give me the names of the
-- Researchers these planets have been observed by;
-- Further, only include those planets who are orbitted by at least one Explored Satellite
-- Further, only include the Observations done before the Exploration date


-- return planet id and name of the planets orbited by one or more EXPLORED satellites
SELECT P.PlanetID, P.PName
FROM Planets P INNER JOIN(
	-- Returns the planet IDs (Duplicates removed) that are orbitted by more than 1 of these satellites
	-- (110 -> p100,   112 + 113 -> p101) => just p101
	SELECT S.PID, COUNT(*) NrSat
	FROM Satellites S INNER JOIN (
		-- Returns the IDs of explored satellites (110, 112, 113)
		SELECT E.SatID
		FROM Explore E
		GROUP BY E.SatID
	) t ON S.SatID=t.SatID
	GROUP BY S.PID
	HAVING COUNT(*)>1) t
ON t.PID=P.PlanetID

-- returns info about the researchers & observation count on those who have made observations
-- on those planets which have satellites which have been explored (by astronauts)
SELECT *
FROM Researchers R INNER JOIN(
	-- Returns the Observation Researcher ID and the count of obs of this type
	SELECT O.RID, COUNT(*) NrObsType1
	FROM Observe O INNER JOIN(
		-- Returns Planet ID, the Nr of sattelites that it is orbited by and the earliest exploration date of the sat
			SELECT S.PID, COUNT(*) NrSat, MIN(t.EarliestExplorationDate) EarliestExplorationDate
			FROM Satellites S INNER JOIN (
				-- Returns Sattelite ID and its earliest exploration date
				SELECT E.SatID, MIN(E.DoEXP) EarliestExplorationDate
				FROM Explore E
				GROUP BY E.SatID
			) t ON S.SatID=t.SatID
			GROUP BY S.PID
			HAVING COUNT(*)>0
		
	) t3 ON t3.PID = O.PID
	--WHERE O.DoOBS < t3.
	GROUP BY O.RID
) t4 ON t4.RID = R.ResearcherID


--we want the date of the observation to be before the date of the exploration
--(so, we pick the earliest exploration date for that specific satellite)
SELECT E.SatID, MIN(E.DoEXP)
FROM Explore E
GROUP BY E.SatID

-- the satellites which have been explored (i don't care about how many times)
SELECT TOP 2 E.SatID
FROM Explore E
GROUP BY E.SatID
	--INNER JOIN Satellites S ON P.PlanetID=S.SatID
	--INNER JOIN Explore E ON S.SatID=E.SatID
	--INNER JOIN Astronauts A ON E.AstronautID=A.AstronautID

--Find all researchers with a specific nr of observations
--find all researchers with the *something computed in a subquery*
--nr Obs not inconclusive < nr obs inconclusive

-- planet ID and average distance at which stars are seen, with the average distance smaller than the max distance
SELECT P.PlanetID, AVG(V.Distance)
FROM Planets P INNER JOIN IsVisible V ON P.PlanetID=V.PlanetID
GROUP BY P.PlanetID
HAVING AVG(V.Distance)<(
		SELECT MAX(V.Distance)
		FROM IsVisible V
		)

-- Return the data of the planet with the biggest density
SELECT *
FROM Planets P
WHERE P.PDensity = ANY(
		SELECT MAX(P2.PDensity)
		FROM Planets P2)

-- find the planets with density smaller than all populated planets
SELECT *
FROM Planets P
WHERE P.PDensity < ALL(
		SELECT P2.PDensity
		FROM Planets P2
		WHERE P2.PPopulation>0
		)
-- ///////////////////////////////////////////////////////////////////////////
SELECT R.ResearcherID, COUNT(*) NrObservations
FROM Researchers R INNER JOIN Observe ON R.ResearcherID = Observe.RID
--WHERE R.RDepartment = 'chemistry'
GROUP BY R.ResearcherID
HAVING COUNT(*)> ANY(
		-- Returns the nr of researchers that have (any nr of) obs marked inconclusive ???
		-- Returns the nr of inconclusive obs. How do we return the nr of researchers with inconclusive obs?
		SELECT COUNT(*)
		FROM Observe O
		WHERE O.Obs='inconclusive' 
		AND R.ResearcherID=O.RID
		--GROUP BY O.RID
)
ORDER BY NrObservations

--return researchers with nrObs bigger than the nr of obs of any other researcher that observed earth
SELECT COUNT(*) AS NrObs
FROM Observe O
GROUP BY O.PID
HAVING COUNT(*) > (
		SELECT COUNT(*)
		FROM Observe O INNER JOIN Planets P ON P.PlanetID=O.PID
		WHERE P.PName='Earth' AND P.PlanetID=O.PID
		)

-- Returns the researcher ID and NrObs, for each researcher with nr of researchers > than the nr of observations on planet named Earth
SELECT TOP 2 R.ResearcherID, COUNT(*) AS NrObs
FROM Observe O INNER JOIN Researchers R ON R.ResearcherID = O.RID
GROUP BY R.ResearcherID
HAVING COUNT(*) > (
	-- Returns nr of observed planets named Earth
    SELECT COUNT(*)
    FROM Observe O INNER JOIN Planets P ON P.PlanetID = O.PID
    WHERE P.PName = 'Earth' AND R.ResearcherID = O.RID
)
ORDER BY R.ResearcherID

SELECT RDepartment FROM Researchers

SELECT DISTINCT R.RDepartment
FROM Researchers R

SELECT S.PID FROM Satellites S

SELECT DISTINCT S.PID FROM Satellites S