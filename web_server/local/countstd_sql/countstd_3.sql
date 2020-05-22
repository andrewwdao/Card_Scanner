-- phpMyAdmin SQL Dump
-- version 5.0.2
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: May 22, 2020 at 09:21 AM
-- Server version: 10.4.11-MariaDB
-- PHP Version: 7.4.6

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `countstd`
--

-- --------------------------------------------------------

--
-- Table structure for table `admin`
--

CREATE TABLE `admin` (
  `id` int(10) UNSIGNED NOT NULL,
  `taikhoan` varchar(50) COLLATE utf8mb4_unicode_ci NOT NULL,
  `password` varchar(255) COLLATE utf8mb4_unicode_ci NOT NULL,
  `remember_token` varchar(100) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `created_at` timestamp NULL DEFAULT NULL,
  `updated_at` timestamp NULL DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Dumping data for table `admin`
--

INSERT INTO `admin` (`id`, `taikhoan`, `password`, `remember_token`, `created_at`, `updated_at`) VALUES
(2, 'admin', '$2y$10$Te4KF2jcZHhILHoMu.5O1.RXPSvPhGqZIl7.pk3eRP3dyrkqkpKq.', NULL, NULL, NULL),
(3, 'nhuttran@natlabs.net', '$2y$10$YcJucif29sEUakcta3Lyq.rMFkGguKewhtTSBt9.gslhdezdeC8zG', NULL, NULL, NULL),
(4, 'quangthong@natlabs.net', '$2y$10$JluRDtB9sMV4ZzaZc5ONi.dUcHqdBloKZnrrBkQvHaS0p/uP3Jcuy', NULL, NULL, NULL),
(5, 'minhan@natlabs.net', '$2y$10$XPl42ZJiW2j.AzPDMrqfj.VHHy5KfHWRSFzpTYjuBN9eZ2/Q7v1wC', NULL, NULL, NULL);

-- --------------------------------------------------------

--
-- Table structure for table `diemdanh`
--

CREATE TABLE `diemdanh` (
  `id` int(10) NOT NULL,
  `id_sinhvien` int(10) NOT NULL,
  `id_mon` int(10) NOT NULL,
  `thoi_gian` datetime NOT NULL DEFAULT current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

-- --------------------------------------------------------

--
-- Table structure for table `monhoc`
--

CREATE TABLE `monhoc` (
  `id` int(10) NOT NULL,
  `ma_mon` varchar(8) COLLATE utf8_unicode_ci NOT NULL,
  `ten_mon` varchar(50) COLLATE utf8_unicode_ci NOT NULL,
  `hoc_ky` int(1) DEFAULT NULL,
  `nam_hoc` int(4) DEFAULT NULL,
  `so_buoi` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- Dumping data for table `monhoc`
--

INSERT INTO `monhoc` (`id`, `ma_mon`, `ten_mon`, `hoc_ky`, `nam_hoc`, `so_buoi`) VALUES
(4, 'AAAAA-C2', 'AAAAAAAAAAAAA', 2, 2222, 33),
(5, 'BBBBF-S7', 'BBBBBBBBBBB', 2, 2222, 44);

-- --------------------------------------------------------

--
-- Table structure for table `sinhvien`
--

CREATE TABLE `sinhvien` (
  `id` int(10) NOT NULL,
  `mssv` char(8) COLLATE utf8_unicode_ci NOT NULL,
  `ho` varchar(50) COLLATE utf8_unicode_ci NOT NULL,
  `ten` varchar(50) COLLATE utf8_unicode_ci NOT NULL,
  `gioi_tinh` tinyint(1) NOT NULL,
  `id_mon` int(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- Dumping data for table `sinhvien`
--

INSERT INTO `sinhvien` (`id`, `mssv`, `ho`, `ten`, `gioi_tinh`, `id_mon`) VALUES
(5, 'B1231321', 'LSDKFJ', 'SLKDFJ', 1, 4),
(6, 'BBBBB333', 'BB2', 'BBBBB', 0, 5);

--
-- Indexes for dumped tables
--

--
-- Indexes for table `admin`
--
ALTER TABLE `admin`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `admin_taikhoan_unique` (`taikhoan`);

--
-- Indexes for table `diemdanh`
--
ALTER TABLE `diemdanh`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `monhoc`
--
ALTER TABLE `monhoc`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `sinhvien`
--
ALTER TABLE `sinhvien`
  ADD PRIMARY KEY (`id`) USING BTREE;

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `admin`
--
ALTER TABLE `admin`
  MODIFY `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=6;

--
-- AUTO_INCREMENT for table `diemdanh`
--
ALTER TABLE `diemdanh`
  MODIFY `id` int(10) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `monhoc`
--
ALTER TABLE `monhoc`
  MODIFY `id` int(10) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=6;

--
-- AUTO_INCREMENT for table `sinhvien`
--
ALTER TABLE `sinhvien`
  MODIFY `id` int(10) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=7;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
