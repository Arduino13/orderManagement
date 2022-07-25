-- MySQL dump 10.17  Distrib 10.3.22-MariaDB, for debian-linux-gnueabihf (armv8l)
--
-- Host: localhost    Database: koukal
-- ------------------------------------------------------
-- Server version	10.3.22-MariaDB-0+deb10u1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `controls`
--

DROP TABLE IF EXISTS `controls`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `controls` (
  `id` varchar(36) COLLATE cp1250_czech_cs NOT NULL,
  `date_from` datetime NOT NULL,
  `date_to` datetime DEFAULT NULL,
  `user_id` text COLLATE cp1250_czech_cs NOT NULL,
  `state` int(11) NOT NULL,
  `batch` text COLLATE cp1250_czech_cs NOT NULL,
  `number` text COLLATE cp1250_czech_cs NOT NULL,
  `number_of` int(11) DEFAULT 0,
  `count` text COLLATE cp1250_czech_cs NOT NULL,
  `reason` text COLLATE cp1250_czech_cs DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=cp1250 COLLATE=cp1250_czech_cs;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `history_con`
--

DROP TABLE IF EXISTS `history_con`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `history_con` (
  `id` text COLLATE cp1250_czech_cs NOT NULL,
  `date` datetime NOT NULL,
  `user_id` text COLLATE cp1250_czech_cs NOT NULL,
  `state` int(11) NOT NULL,
  PRIMARY KEY (`date`)
) ENGINE=InnoDB DEFAULT CHARSET=cp1250 COLLATE=cp1250_czech_cs;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `history_rec`
--

DROP TABLE IF EXISTS `history_rec`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `history_rec` (
  `id` varchar(36) COLLATE cp1250_czech_cs NOT NULL,
  `date` datetime NOT NULL,
  `user_id` text COLLATE cp1250_czech_cs NOT NULL,
  `state` int(11) NOT NULL,
  PRIMARY KEY (`date`)
) ENGINE=InnoDB DEFAULT CHARSET=cp1250 COLLATE=cp1250_czech_cs;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `items`
--

DROP TABLE IF EXISTS `items`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `items` (
  `id` varchar(36) COLLATE cp1250_czech_cs NOT NULL,
  `number` text COLLATE cp1250_czech_cs NOT NULL,
  `type_thread_l` text COLLATE cp1250_czech_cs DEFAULT NULL,
  `type_thread_r` text COLLATE cp1250_czech_cs DEFAULT NULL,
  `current` text COLLATE cp1250_czech_cs DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=cp1250 COLLATE=cp1250_czech_cs;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `records`
--

DROP TABLE IF EXISTS `records`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `records` (
  `id` varchar(36) COLLATE cp1250_czech_cs NOT NULL,
  `date_from` datetime NOT NULL,
  `date_to` datetime DEFAULT NULL,
  `user_id` text COLLATE cp1250_czech_cs NOT NULL,
  `state` int(11) NOT NULL,
  `batch` text COLLATE cp1250_czech_cs NOT NULL,
  `number` text COLLATE cp1250_czech_cs NOT NULL,
  `screw` text COLLATE cp1250_czech_cs DEFAULT NULL,
  `number_of` int(11) DEFAULT 0,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=cp1250 COLLATE=cp1250_czech_cs;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `setting`
--

DROP TABLE IF EXISTS `setting`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `setting` (
  `id` varchar(36) COLLATE cp1250_czech_cs NOT NULL,
  `value` text COLLATE cp1250_czech_cs NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=cp1250 COLLATE=cp1250_czech_cs;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `users`
--

DROP TABLE IF EXISTS `users`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `users` (
  `id` varchar(36) COLLATE cp1250_czech_cs NOT NULL,
  `card_number` text COLLATE cp1250_czech_cs NOT NULL,
  `name` text COLLATE cp1250_czech_cs NOT NULL,
  `last_updated` text COLLATE cp1250_czech_cs DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=cp1250 COLLATE=cp1250_czech_cs;
/*!40101 SET character_set_client = @saved_cs_client */;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2022-07-25 21:37:54
