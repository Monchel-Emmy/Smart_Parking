-- phpMyAdmin SQL Dump
-- version 5.2.0
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Mar 29, 2025 at 03:28 PM
-- Server version: 10.4.25-MariaDB
-- PHP Version: 8.1.10

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `smart_parking_system`
--

-- --------------------------------------------------------

--
-- Table structure for table `customers`
--

CREATE TABLE `customers` (
  `id` int(11) NOT NULL,
  `uid` varchar(50) NOT NULL,
  `name` varchar(100) NOT NULL,
  `balance` float NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `customers`
--

INSERT INTO `customers` (`id`, `uid`, `name`, `balance`) VALUES
(6, 'D6F62B96', 'Jean Claude', 32800),
(19, 'F732B385', 'Emmanuel Tuyisenge', 28400),
(20, '6F2AB889', 'Kamanzi', 6000),
(21, '10867A51', 'Kellia', 200),
(22, '13BF94E5', 'David', 0),
(25, '8E0ADC21', 'TapandGo', 9400);

-- --------------------------------------------------------

--
-- Table structure for table `transactions`
--

CREATE TABLE `transactions` (
  `id` int(11) NOT NULL,
  `uid` varchar(50) NOT NULL,
  `entry_time` datetime DEFAULT NULL,
  `exit_time` datetime DEFAULT NULL,
  `duration` float DEFAULT NULL,
  `cost` float DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `transactions`
--

INSERT INTO `transactions` (`id`, `uid`, `entry_time`, `exit_time`, `duration`, `cost`) VALUES
(43, 'F732B385', '2025-01-31 22:39:49', '2025-01-31 22:41:33', 2, 400),
(44, 'D6F62B96', '2025-01-31 22:54:25', '2025-01-31 22:57:24', 3, 600),
(45, '10867A51', '2025-01-31 22:55:01', '2025-01-31 22:58:45', 4, 800),
(46, 'F732B385', '2025-01-31 22:55:22', '2025-01-31 22:55:57', 1, 200),
(47, 'D6F62B96', '2025-01-31 22:59:52', '2025-01-31 23:02:33', 3, 600),
(48, 'F732B385', '2025-02-03 13:38:57', '2025-02-03 13:41:30', 3, 600),
(49, '8E0ADC21', '2025-02-03 13:45:24', '2025-02-03 13:47:31', 3, 600),
(50, 'F732B385', '2025-02-06 18:39:36', '2025-02-06 18:44:04', 5, 1000),
(51, 'D6F62B96', '2025-02-06 18:39:50', '2025-02-06 18:41:40', 2, 400),
(52, 'D6F62B96', '2025-02-08 13:48:42', '2025-02-08 13:49:21', 1, 200),
(53, 'D6F62B96', '2025-02-08 13:49:47', '2025-02-08 13:50:03', 1, 200),
(54, 'F732B385', '2025-02-08 13:53:00', '2025-02-08 13:55:06', 3, 600),
(55, 'D6F62B96', '2025-03-15 13:01:20', '2025-03-15 13:12:45', 12, 2400),
(56, 'F732B385', '2025-03-15 13:02:00', '2025-03-15 13:12:02', 11, 2200),
(57, 'D6F62B96', '2025-03-15 13:14:39', '2025-03-15 13:27:26', 13, 2600),
(58, 'F732B385', '2025-03-15 13:16:51', '2025-03-15 13:27:15', 11, 2200),
(60, 'D6F62B96', '2025-03-15 13:31:19', '2025-03-15 13:32:47', 2, 400),
(61, 'D6F62B96', '2025-03-15 13:33:17', '2025-03-15 13:33:33', 1, 200),
(62, 'F732B385', '2025-03-15 13:36:40', '2025-03-15 13:36:52', 1, 200),
(63, 'D6F62B96', '2025-03-15 13:46:00', '2025-03-15 13:46:06', 1, 200),
(64, 'F732B385', '2025-03-15 14:12:50', '2025-03-15 14:13:01', 1, 200);

--
-- Indexes for dumped tables
--

--
-- Indexes for table `customers`
--
ALTER TABLE `customers`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `uid` (`uid`);

--
-- Indexes for table `transactions`
--
ALTER TABLE `transactions`
  ADD PRIMARY KEY (`id`),
  ADD KEY `uid` (`uid`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `customers`
--
ALTER TABLE `customers`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=26;

--
-- AUTO_INCREMENT for table `transactions`
--
ALTER TABLE `transactions`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=82;

--
-- Constraints for dumped tables
--

--
-- Constraints for table `transactions`
--
ALTER TABLE `transactions`
  ADD CONSTRAINT `transactions_ibfk_1` FOREIGN KEY (`uid`) REFERENCES `customers` (`uid`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
