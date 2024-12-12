-- Create table MasterData
CREATE TABLE MasterData (
  `MasterID` INT AUTO_INCREMENT PRIMARY KEY,
  `Username` VARCHAR(50) DEFAULT 'Null',
  `Password` VARCHAR(64) DEFAULT 'Null',
  `Alias1` VARCHAR(24) DEFAULT 'Null',
  `Alias2` VARCHAR(24) DEFAULT 'Null',
  `Alias3` VARCHAR(24) DEFAULT 'Null'
);

-- Create table PlayerData
CREATE TABLE PlayerData (
  `PlayerID` INT(4) AUTO_INCREMENT PRIMARY KEY,
  `MasterID` INT(4) DEFAULT 0,
  `Name` VARCHAR(24) DEFAULT 'Null',
  `Code` INT(4) DEFAULT NULL,
  `Skin` INT(6) DEFAULT 0,
  `Health` INT(3) DEFAULT 100,
  `Armor` INT(3) DEFAULT 100,
  `Hunger` INT(3) DEFAULT 100,
  `Thirst` INT(3) DEFAULT 100,
  `PosX` FLOAT DEFAULT 0.0,
  `PosY` FLOAT DEFAULT 0.0,
  `PosZ` FLOAT DEFAULT 0.0,
  `PosA` FLOAT DEFAULT 0.0
);

-- Create table TrustedDevices
CREATE TABLE TrustedDevices (
  `TrustedID` INT AUTO_INCREMENT PRIMARY KEY,
  `MasterID` INT NOT NULL,
  `DeviceHash` VARCHAR(128) NOT NULL,
  `LastUsedIP` VARCHAR(45) NOT NULL,
  `AddedTimestamp` DATETIME DEFAULT CURRENT_TIMESTAMP
);