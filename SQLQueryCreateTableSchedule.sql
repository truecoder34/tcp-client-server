USE DB_Railway_CB;
CREATE TABLE Schedule(
	TrainID INT PRIMARY KEY,
	StationFirst VARCHAR(255) NOT NULL,
	StationSecond VARCHAR(255) NOT NULL,
	TimeDepart DATETIME,
	TimeArrive DATETIME,
	PlacesA INT,
	PlacesB INT,
	PlacesC INT,
	CostA INT,
	CostB INT,
	CostC INT
)