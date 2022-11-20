CREATE DATABASE  IF NOT EXISTS `bank` /*!40100 DEFAULT CHARACTER SET utf8mb3 */ /*!80016 DEFAULT ENCRYPTION='N' */;
USE `bank`;
-- MySQL dump 10.13  Distrib 8.0.30, for Win64 (x86_64)
--
-- Host: 127.0.0.1    Database: bank
-- ------------------------------------------------------
-- Server version	8.0.29

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `account`
--

DROP TABLE IF EXISTS `account`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `account` (
  `idaccount` int NOT NULL,
  `saldo` int DEFAULT NULL,
  `accounttype` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`idaccount`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `account`
--

LOCK TABLES `account` WRITE;
/*!40000 ALTER TABLE `account` DISABLE KEYS */;
INSERT INTO `account` VALUES (1,20,'debit'),(2,1200,'debit'),(3,0,'credit'),(4,100,'debit'),(1111,1600,'debit');
/*!40000 ALTER TABLE `account` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `action`
--

DROP TABLE IF EXISTS `action`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `action` (
  `idaction` int NOT NULL AUTO_INCREMENT,
  `idcard` int DEFAULT NULL,
  `idaccount` int DEFAULT NULL,
  `action_time` date DEFAULT NULL,
  `amount` int DEFAULT NULL,
  PRIMARY KEY (`idaction`),
  KEY `card_id_idx` (`idcard`),
  KEY `account_id2_idx` (`idaccount`),
  CONSTRAINT `account_id2` FOREIGN KEY (`idaccount`) REFERENCES `account` (`idaccount`) ON DELETE RESTRICT ON UPDATE CASCADE,
  CONSTRAINT `card_id` FOREIGN KEY (`idcard`) REFERENCES `card` (`idcard`) ON DELETE RESTRICT ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `action`
--

LOCK TABLES `action` WRITE;
/*!40000 ALTER TABLE `action` DISABLE KEYS */;
INSERT INTO `action` VALUES (1,NULL,2,'2022-11-20',100),(2,NULL,2,'2022-11-20',100),(3,NULL,1111,'2022-11-20',100);
/*!40000 ALTER TABLE `action` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `card`
--

DROP TABLE IF EXISTS `card`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `card` (
  `idcard` int NOT NULL,
  `password` varchar(255) DEFAULT NULL,
  `idaccount` int DEFAULT NULL,
  `idcustomer` int DEFAULT NULL,
  PRIMARY KEY (`idcard`),
  KEY `bank_account_idx` (`idaccount`),
  KEY `customer_id_idx` (`idcustomer`),
  CONSTRAINT `account_id` FOREIGN KEY (`idaccount`) REFERENCES `account` (`idaccount`) ON DELETE RESTRICT ON UPDATE CASCADE,
  CONSTRAINT `customer_id` FOREIGN KEY (`idcustomer`) REFERENCES `customer` (`idcustomer`) ON DELETE RESTRICT ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `card`
--

LOCK TABLES `card` WRITE;
/*!40000 ALTER TABLE `card` DISABLE KEYS */;
INSERT INTO `card` VALUES (1,'1111',1,1),(2,'2222',2,2),(3,'3333',3,3),(4,'4444',3,4);
/*!40000 ALTER TABLE `card` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `customer`
--

DROP TABLE IF EXISTS `customer`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `customer` (
  `idcustomer` int NOT NULL,
  `customername` varchar(45) DEFAULT NULL,
  `address` varchar(45) DEFAULT NULL,
  `phonenumber` varchar(15) DEFAULT NULL,
  PRIMARY KEY (`idcustomer`),
  UNIQUE KEY `idcustomer_UNIQUE` (`idcustomer`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `customer`
--

LOCK TABLES `customer` WRITE;
/*!40000 ALTER TABLE `customer` DISABLE KEYS */;
INSERT INTO `customer` VALUES (1,'Aku Ankka','Paratiisitie 13',' 555 258'),(2,'Mikki Hiiri','Ankkalinna','555 64554'),(3,'Mortti','Ankkalinna','555 667884'),(4,'Vertti','Ankalinna','555 837884');
/*!40000 ALTER TABLE `customer` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping routines for database 'bank'
--
/*!50003 DROP PROCEDURE IF EXISTS `debit_transfer` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_0900_ai_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `debit_transfer`(IN first_id INT, IN second_id INT, IN amount DOUBLE )
BEGIN
  DECLARE test1, test2 INT DEFAULT 0;
  START TRANSACTION;
  UPDATE account SET saldo=saldo-amount WHERE idaccount=first_id AND saldo>=amount;
  SET test1=ROW_COUNT();
  UPDATE account SET saldo=saldo-amount WHERE idaccount=second_id;
  SET test2=ROW_COUNT();
    IF (test1 > 0 AND test2 >0) THEN
      COMMIT;
      INSERT INTO action(idaccount,amount,action_time) VALUES(first_id,amount, NOW());
      INSERT INTO action(idaccount,amount,action_time) VALUES(second_id,amount, NOW());
    ELSE
      ROLLBACK;
  END IF;
END ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2022-11-20 20:26:51
