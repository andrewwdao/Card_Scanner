-- phpMyAdmin SQL Dump
-- version 5.0.2
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: May 22, 2020 at 01:55 PM
-- Server version: 10.4.11-MariaDB
-- PHP Version: 7.3.18

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
(7, 'admin', '$2y$10$YxkSRpfNmWSOf0sxrkdt9eFuXk20YR8pN9DBGtjdVGqiyXVq4gEJC', NULL, NULL, NULL);

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

--
-- Dumping data for table `diemdanh`
--

INSERT INTO `diemdanh` (`id`, `id_sinhvien`, `id_mon`, `thoi_gian`) VALUES
(33, 32, 16, '2020-05-22 18:54:25'),
(34, 33, 16, '2020-05-22 18:54:36'),
(35, 34, 16, '2020-05-22 18:54:46'),
(36, 35, 16, '2020-05-22 18:54:54');

-- --------------------------------------------------------

--
-- Table structure for table `monhoc`
--

CREATE TABLE `monhoc` (
  `id` int(10) NOT NULL,
  `ma_mon` varchar(8) COLLATE utf8_unicode_ci NOT NULL,
  `ten_mon` varchar(50) COLLATE utf8_unicode_ci NOT NULL,
  `hoc_ky` int(1) DEFAULT NULL,
  `nam_hoc` char(9) COLLATE utf8_unicode_ci DEFAULT NULL,
  `so_buoi` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- Dumping data for table `monhoc`
--

INSERT INTO `monhoc` (`id`, `ma_mon`, `ten_mon`, `hoc_ky`, `nam_hoc`, `so_buoi`) VALUES
(16, 'TN123-S2', 'Vi điều khiển', 1, '2019-2020', 30);

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
(32, 'B1509360', 'Đào', 'Minh An', 1, 16),
(33, 'B1805880', 'Trần', 'Anh Khôi', 1, 16),
(34, 'B1509482', 'Dương Phạm', 'Quang Thông', 1, 16),
(35, 'B1509397', 'Trần', 'Quang Nhựt', 1, 16);

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
  MODIFY `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=8;

--
-- AUTO_INCREMENT for table `diemdanh`
--
ALTER TABLE `diemdanh`
  MODIFY `id` int(10) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=37;

--
-- AUTO_INCREMENT for table `monhoc`
--
ALTER TABLE `monhoc`
  MODIFY `id` int(10) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=17;

--
-- AUTO_INCREMENT for table `sinhvien`
--
ALTER TABLE `sinhvien`
  MODIFY `id` int(10) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=36;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
