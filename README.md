# 职工信息管理系统 (Employee Information Management System)

这是一个使用标准 C 语言编写的职工信息管理系统，支持职工记录的增删改查、排序、部门分析以及文件持久化。

## 功能特性

- **添加记录**：录入职工编号、姓名、部门、职称、各项工资等。
- **查询功能**：支持按编号或姓名精准查询。
- **排序功能**：支持按总工资或基本工资降序排列。
- **删除与修改**：灵活管理现有职工数据。
- **部门分析**：自动计算部门平均工资，统计各职称人数及占比。
- **数据持久化**：自动保存数据至 `employees.txt`。

## 如何编译运行

### Windows
1.  安装 MinGW 或 GCC。
2.  运行编译命令：
    ```bash
    gcc -o manager main.c
    ```
3.  执行：
    ```bash
    manager.exe
    ```

### macOS/Linux
1.  使用自带的 GCC/Clang。
2.  运行编译命令：
    ```bash
    gcc -o manager main.c
    ```
3.  执行：
    ```bash
    ./manager
    ```

## 自动化构建

本项目已配置 GitHub Actions。每当您推送代码至仓库时，系统会自动在云端构建 Windows 版本的可执行文件 (`.exe`)，您可以直接在 GitHub 的 **Releases** 或 **Actions** 页面下载构建产物。
