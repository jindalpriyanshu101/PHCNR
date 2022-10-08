-- MySQL dump 10.16  Distrib 10.1.9-MariaDB, for Win32 (AMD64)
--
-- Host: 127.0.0.1   Database: server_175_CSFCNR
-- ------------------------------------------------------
-- Server version	10.1.9-MariaDB

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `gang`
--

DROP TABLE IF EXISTS `gang`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `gang` (
  `id` int(10) NOT NULL AUTO_INCREMENT,
  `name` varchar(30) NOT NULL,
  `color` varchar(6) NOT NULL,
  `score` int(10) NOT NULL DEFAULT '0',
  `gangslot` smallint(6) NOT NULL DEFAULT '12',
  `kills` int(11) NOT NULL DEFAULT '0',
  `deaths` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `gang`
--

LOCK TABLES `gang` WRITE;
/*!40000 ALTER TABLE `gang` DISABLE KEYS */;
/*!40000 ALTER TABLE `gang` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `playerbans`
--

DROP TABLE IF EXISTS `playerbans`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `playerbans` (
  `ban_id` int(6) NOT NULL AUTO_INCREMENT,
  `banned_by` varchar(24) NOT NULL,
  `banned_for` varchar(128) NOT NULL,
  `player_banned` varchar(24) NOT NULL,
  `player_ip` varchar(15) NOT NULL,
  PRIMARY KEY (`ban_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `playerbans`
--

LOCK TABLES `playerbans` WRITE;
/*!40000 ALTER TABLE `playerbans` DISABLE KEYS */;
/*!40000 ALTER TABLE `playerbans` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `playerdata`
--

DROP TABLE IF EXISTS `playerdata`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `playerdata` (
  `playerName` varchar(30) NOT NULL,
  `playerPass` varchar(500) NOT NULL,
  `playerScore` varchar(10) NOT NULL DEFAULT '0',
  `playerMoney` varchar(10) NOT NULL DEFAULT '0',
  `playerIP` varchar(20) NOT NULL DEFAULT '0',
  `playerLevel` int(3) NOT NULL DEFAULT '0',
  `playerKills` int(10) NOT NULL DEFAULT '0',
  `playerDeaths` int(10) NOT NULL DEFAULT '0',
  `playerRobberies` int(10) NOT NULL DEFAULT '0',
  `playerJailTime` int(10) NOT NULL DEFAULT '0',
  `playerTimesJailed` int(10) NOT NULL DEFAULT '0',
  `playerWantedLevel` int(10) NOT NULL DEFAULT '0',
  `playerVIP` int(3) NOT NULL DEFAULT '0',
  `playerMuteTime` int(10) NOT NULL DEFAULT '0',
  `playerXP` int(8) NOT NULL DEFAULT '0',
  `playerJob` int(3) NOT NULL DEFAULT '-1',
  `playerCopBanned` int(1) NOT NULL DEFAULT '0',
  `playerArmyBanned` int(1) NOT NULL DEFAULT '0',
  `playerFightStyle` int(2) NOT NULL DEFAULT '0',
  `playerID` int(10) NOT NULL AUTO_INCREMENT,
  `playerHitValue` int(10) NOT NULL DEFAULT '0',
  `playerAdminJailed` int(1) NOT NULL DEFAULT '0',
  `playerBank` int(100) NOT NULL DEFAULT '0',
  `copTutorial` int(1) NOT NULL DEFAULT '0',
  `lastLogged` varchar(100) NOT NULL DEFAULT 'Never',
  `playerHelper` int(1) NOT NULL DEFAULT '0',
  `playerWeed` int(3) NOT NULL DEFAULT '0',
  `firstLogged` int(20) NOT NULL,
  `vipExpires` int(20) NOT NULL DEFAULT '-1',
  `statTrucks` int(4) NOT NULL DEFAULT '0',
  `vipweapon` int(3) NOT NULL DEFAULT '0',
  `arrestStat` int(4) NOT NULL DEFAULT '0',
  `moneybagStat` int(3) NOT NULL DEFAULT '0',
  `rules_read` int(1) NOT NULL DEFAULT '0',
  `spawnHouse` int(3) NOT NULL DEFAULT '-1',
  `statHits` int(3) NOT NULL DEFAULT '0',
  `streetRobberies` int(4) NOT NULL DEFAULT '0',
  `streetRapes` int(4) NOT NULL DEFAULT '0',
  `playersTied` int(4) NOT NULL DEFAULT '0',
  `playersKidnapped` int(4) NOT NULL DEFAULT '0',
  `copDetains` int(4) NOT NULL DEFAULT '0',
  `copKills` int(4) NOT NULL DEFAULT '0',
  `playerRope` int(4) NOT NULL DEFAULT '0',
  `playerBobbyPins` int(4) NOT NULL DEFAULT '0',
  `playerScissors` int(4) NOT NULL DEFAULT '0',
  `playerExplosives` int(4) NOT NULL DEFAULT '0',
  `forkliftCompleted` int(4) NOT NULL DEFAULT '0',
  `bankRobs` int(4) NOT NULL DEFAULT '0',
  `innocentKills` int(3) NOT NULL DEFAULT '0',
  `aInnocentKills` int(3) NOT NULL DEFAULT '0',
  `customSkin` int(3) NOT NULL DEFAULT '-1',
  `busCompleted` int(3) NOT NULL DEFAULT '0',
  `dm_kills` int(4) NOT NULL DEFAULT '0',
  `dm_deaths` int(4) NOT NULL DEFAULT '0',
  `cookies` int(4) NOT NULL DEFAULT '0',
  `backpack` int(1) NOT NULL DEFAULT '0',
  `sweepCompleted` int(3) NOT NULL DEFAULT '0',
  `weaponSkill` int(1) NOT NULL DEFAULT '0',
  `bombsDefused` int(3) NOT NULL DEFAULT '0',
  `rTokens` int(5) NOT NULL DEFAULT '0',
  `gang` int(11) NOT NULL DEFAULT '0',
  `gangstatus` tinyint(1) NOT NULL DEFAULT '0',
  PRIMARY KEY (`playerID`),
  UNIQUE KEY `playerName` (`playerName`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `playerdata`
--

LOCK TABLES `playerdata` WRITE;
/*!40000 ALTER TABLE `playerdata` DISABLE KEYS */;
/*!40000 ALTER TABLE `playerdata` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `ucp_ban`
--

DROP TABLE IF EXISTS `ucp_ban`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ucp_ban` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `playerID` int(11) NOT NULL,
  `reason` varchar(50) NOT NULL,
  `banner` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `ucp_ban`
--

LOCK TABLES `ucp_ban` WRITE;
/*!40000 ALTER TABLE `ucp_ban` DISABLE KEYS */;
/*!40000 ALTER TABLE `ucp_ban` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `ucp_data`
--

DROP TABLE IF EXISTS `ucp_data`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ucp_data` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `playerID` int(11) NOT NULL,
  `profile_pic` varchar(50) NOT NULL,
  `update_time` int(11) NOT NULL,
  `about` varchar(200) NOT NULL,
  `facebook` varchar(100) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `playerID` (`playerID`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `ucp_data`
--

LOCK TABLES `ucp_data` WRITE;
/*!40000 ALTER TABLE `ucp_data` DISABLE KEYS */;
INSERT INTO `ucp_data` VALUES (1,110781,'X337.jpg',1464614753,'Fuck','bondowocopzz'),(2,107379,'default.jpg',1464614734,'','');
/*!40000 ALTER TABLE `ucp_data` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `ucp_friends`
--

DROP TABLE IF EXISTS `ucp_friends`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ucp_friends` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `playerID` int(11) NOT NULL,
  `requestBy` int(11) NOT NULL,
  `status` tinyint(1) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `ucp_friends`
--

LOCK TABLES `ucp_friends` WRITE;
/*!40000 ALTER TABLE `ucp_friends` DISABLE KEYS */;
INSERT INTO `ucp_friends` VALUES (1,110781,107379,1);
/*!40000 ALTER TABLE `ucp_friends` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `ucp_like`
--

DROP TABLE IF EXISTS `ucp_like`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ucp_like` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `playerID` int(11) NOT NULL,
  `toPlayer` int(11) NOT NULL,
  `status` tinyint(1) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `ucp_like`
--

LOCK TABLES `ucp_like` WRITE;
/*!40000 ALTER TABLE `ucp_like` DISABLE KEYS */;
INSERT INTO `ucp_like` VALUES (1,107379,110781,1);
/*!40000 ALTER TABLE `ucp_like` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `ucp_master`
--

DROP TABLE IF EXISTS `ucp_master`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ucp_master` (
  `ann_text` varchar(200) NOT NULL,
  `ann_set_by` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `ucp_master`
--

LOCK TABLES `ucp_master` WRITE;
/*!40000 ALTER TABLE `ucp_master` DISABLE KEYS */;
INSERT INTO `ucp_master` VALUES ('<span style=\"color:yellow\">Fairuz Ganteng</span>',110781);
/*!40000 ALTER TABLE `ucp_master` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `ucp_message`
--

DROP TABLE IF EXISTS `ucp_message`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ucp_message` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `playerID` int(11) NOT NULL,
  `sender` int(11) NOT NULL,
  `message` text NOT NULL,
  `date` int(11) NOT NULL,
  `status` tinyint(1) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `ucp_message`
--

LOCK TABLES `ucp_message` WRITE;
/*!40000 ALTER TABLE `ucp_message` DISABLE KEYS */;
INSERT INTO `ucp_message` VALUES (1,110781,-1,'Welcome to CZCNR Control Panel v1.1 if you want to start a new conversation, go to someone\'s profile and then click \"Send PM\" button.',1458561037,1),(2,107379,-1,'Welcome to CZCNR Control Panel v1.1 if you want to start a new conversation, go to someone\'s profile and then click \"Send PM\" button.',1464614567,1);
/*!40000 ALTER TABLE `ucp_message` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `ucp_shoutbox`
--

DROP TABLE IF EXISTS `ucp_shoutbox`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ucp_shoutbox` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `playerID` int(11) NOT NULL,
  `message` varchar(255) NOT NULL,
  `date` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `ucp_shoutbox`
--

LOCK TABLES `ucp_shoutbox` WRITE;
/*!40000 ALTER TABLE `ucp_shoutbox` DISABLE KEYS */;
INSERT INTO `ucp_shoutbox` VALUES (1,110781,'Shoutbox test',1464614419),(2,110781,'Fuck',1464614423),(3,110781,'Ntar ane login pake akun lain gan',1464614431),(4,110781,'Di chrome',1464614436),(5,107379,'Ini char laen',1464614592),(6,110781,'ostomastis ngapdet gan',1464614608),(7,107379,'gitu gan',1464614619);
/*!40000 ALTER TABLE `ucp_shoutbox` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2016-06-13 14:23:46
