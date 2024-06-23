/*
 Navicat Premium Dump SQL

 Source Server         : project
 Source Server Type    : MySQL
 Source Server Version : 80035 (8.0.35)
 Source Host           : localhost:3306
 Source Schema         : study_plan

 Target Server Type    : MySQL
 Target Server Version : 80035 (8.0.35)
 File Encoding         : 65001

 Date: 23/06/2024 15:15:59
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for study-plans
-- ----------------------------
DROP TABLE IF EXISTS `study-plans`;
CREATE TABLE `study-plans`  (
  `id` int NOT NULL AUTO_INCREMENT COMMENT '主键id用于标识学习计划',
  `username` varchar(10) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL COMMENT '标识创建该计划的用户名称',
  `deadline` datetime NULL DEFAULT NULL COMMENT '学习计划的截止时间',
  `topic` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL COMMENT '学习计划主题',
  `priority` int NULL DEFAULT NULL COMMENT '计划的优先级',
  `content` char(150) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL COMMENT '学习计划的主要内容',
  `create_time` timestamp NULL DEFAULT NULL ON UPDATE CURRENT_TIMESTAMP COMMENT '计划的创建时间',
  `update_time` timestamp NULL DEFAULT NULL ON UPDATE CURRENT_TIMESTAMP COMMENT '计划的修改时间',
  `status` int NULL DEFAULT NULL COMMENT '完成状态',
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE INDEX `study_plans_pk`(`id` ASC) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 133931 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;


DROP TABLE IF EXISTS `user`;
CREATE TABLE `user`  (
  `id` int NOT NULL AUTO_INCREMENT COMMENT '唯一标识',
  `username` varchar(10) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL COMMENT '用户名',
  `password` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '用户的密码',
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE INDEX `user_pk_2`(`username` ASC) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 1022 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci COMMENT = '该表是用来标记用户的表' ROW_FORMAT = Dynamic;

SET FOREIGN_KEY_CHECKS = 1;



