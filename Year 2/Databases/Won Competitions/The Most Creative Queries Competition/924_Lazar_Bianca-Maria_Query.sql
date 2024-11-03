USE ASTRONOMY_DB
GO

-- Returns info about the Researchers who have made Observations on planets which are orbited by EXPLORED satellites
-- only if those Observations were made PRIOR to the earliest exploration date of ANY of its satellites.
-- It also returns the Number of such Observations
SELECT R.ResearcherID, R.RName, R.RDepartment, R.RDoB, t4.NrObsType1
FROM Researchers R INNER JOIN(
	-- Returns the Researcher ID who wrote Observations on Planets that are orbited by EXPLORED Satellites,
	-- and the count of Observations of this type
	SELECT O.RID, COUNT(*) NrObsType1
	FROM Observe O INNER JOIN(
		-- Returns the Planet ID, the nr of sattelites that it is orbited by, and the earliest exploration date of its
		-- first explored satellite
			SELECT S.PID, COUNT(*) NrSat, MIN(t.EarliestExplorationDate) EarliestExplorationDate
			FROM Satellites S INNER JOIN (
				-- Returns the Sattelite ID and its earliest exploration date
				SELECT E.SatID, MIN(E.DoEXP) EarliestExplorationDate
				FROM Explore E
				GROUP BY E.SatID
			) t ON S.SatID=t.SatID
			GROUP BY S.PID
	) t3 ON t3.PID = O.PID
	WHERE O.DoOBS < t3.EarliestExplorationDate
	GROUP BY O.RID
) t4 ON t4.RID = R.ResearcherID

-- Obs: it is irrelevant if multiple researchers wrote observations on the same planet