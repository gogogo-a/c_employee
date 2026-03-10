#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#endif

#define MAX_EMPLOYEES 1000
#define FILENAME "employees.txt"

// 职工结构体定义
typedef struct {
    char id[20];        // 职工编号
    char name[50];      // 姓名
    char dept[50];      // 部门
    char title[50];     // 职称
    double base_salary; // 基本工资
    double extra_salary;// 加班工资
    double bonus;       // 奖金
    double total_salary;// 总工资
} Employee;

Employee emps[MAX_EMPLOYEES];
int emp_count = 0;

// 函数声明
void menu();
void add_employee();
void query_employee();
void sort_employees();
void delete_employee();
void modify_employee();
void analyze_dept();
void output_all();
void load_data();
void save_data();
double calculate_total(Employee *e);
int find_by_id(const char *id);

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
#endif
    load_data();
    int choice;
    while (1) {
        menu();
        printf("\n请选择功能 (0-7): ");
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n'); // 清理缓冲区
            continue;
        }
        
        switch (choice) {
            case 1: add_employee(); break;
            case 2: query_employee(); break;
            case 3: sort_employees(); break;
            case 4: delete_employee(); break;
            case 5: modify_employee(); break;
            case 6: analyze_dept(); break;
            case 7: output_all(); break;
            case 0: 
                save_data();
                printf("感谢使用，系统已退出并保存数据。\n");
                exit(0);
            default: printf("无效选择，请重新输入。\n");
        }
    }
    return 0;
}

void menu() {
    printf("\n==================================\n");
    printf("    职工信息管理系统 (V1.0)       \n");
    printf("==================================\n");
    printf("  (1) 添加职工记录\n");
    printf("  (2) 查询职工 (按编号或姓名)\n");
    printf("  (3) 职工数据排序 (按总工资或基本工资)\n");
    printf("  (4) 删除职工记录\n");
    printf("  (5) 修改职工记录\n");
    printf("  (6) 部门职工分析\n");
    printf("  (7) 输出职工信息表\n");
    printf("  (0) 退出并保存\n");
    printf("==================================\n");
}

double calculate_total(Employee *e) {
    return e->base_salary + e->extra_salary + e->bonus;
}

int find_by_id(const char *id) {
    for (int i = 0; i < emp_count; i++) {
        if (strcmp(emps[i].id, id) == 0) return i;
    }
    return -1;
}

void load_data() {
    FILE *fp = fopen(FILENAME, "r");
    if (!fp) return;
    emp_count = 0;
    while (fscanf(fp, "%s %s %s %s %lf %lf %lf %lf", 
           emps[emp_count].id, emps[emp_count].name, 
           emps[emp_count].dept, emps[emp_count].title, 
           &emps[emp_count].base_salary, &emps[emp_count].extra_salary, 
           &emps[emp_count].bonus, &emps[emp_count].total_salary) == 8) {
        emp_count++;
        if (emp_count >= MAX_EMPLOYEES) break;
    }
    fclose(fp);
}

void save_data() {
    FILE *fp = fopen(FILENAME, "w");
    if (!fp) {
        printf("保存失败：无法打开文件。\n");
        return;
    }
    for (int i = 0; i < emp_count; i++) {
        fprintf(fp, "%s %s %s %s %.2f %.2f %.2f %.2f\n", 
                emps[i].id, emps[i].name, emps[i].dept, emps[i].title, 
                emps[i].base_salary, emps[i].extra_salary, 
                emps[i].bonus, emps[i].total_salary);
    }
    fclose(fp);
}

void add_employee() {
    if (emp_count >= MAX_EMPLOYEES) {
        printf("错误：系统容量已满。\n");
        return;
    }
    Employee e;
    printf("请输入职工编号: "); scanf("%s", e.id);
    if (find_by_id(e.id) != -1) {
        printf("错误：编号为 %s 的职工已存在。\n", e.id);
        return;
    }
    printf("请输入姓名: "); scanf("%s", e.name);
    printf("请输入部门: "); scanf("%s", e.dept);
    printf("请输入职称: "); scanf("%s", e.title);
    printf("基本工资: "); scanf("%lf", &e.base_salary);
    printf("加班工资: "); scanf("%lf", &e.extra_salary);
    printf("奖金: "); scanf("%lf", &e.bonus);
    e.total_salary = calculate_total(&e);
    
    emps[emp_count++] = e;
    printf("添加成功！\n");
}

void output_all() {
    if (emp_count == 0) {
        printf("系统中尚无记录。\n");
        return;
    }
    printf("\n%-10s %-12s %-12s %-10s %-10s %-10s %-10s %-10s\n", 
           "编号", "姓名", "部门", "职称", "基本工资", "加班工资", "奖金", "总工资");
    printf("------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < emp_count; i++) {
        printf("%-10s %-12s %-12s %-10s %-10.2f %-10.2f %-10.2f %-10.2f\n", 
               emps[i].id, emps[i].name, emps[i].dept, emps[i].title, 
               emps[i].base_salary, emps[i].extra_salary, emps[i].bonus, emps[i].total_salary);
    }
}

void query_employee() {
    int q_choice;
    printf("1. 按编号查询  2. 按姓名查询: ");
    scanf("%d", &q_choice);
    
    if (q_choice == 1) {
        char target_id[20];
        printf("请输入查询编号: "); scanf("%s", target_id);
        int idx = find_by_id(target_id);
        if (idx != -1) {
            printf("\n找到记录：\n");
            printf("%-10s %-12s %-12s %-10s %-10.2f %-10.2f %-10.2f %-10.2f\n", 
                   emps[idx].id, emps[idx].name, emps[idx].dept, emps[idx].title, 
                   emps[idx].base_salary, emps[idx].extra_salary, emps[idx].bonus, emps[idx].total_salary);
        } else {
            printf("未找到编号为 %s 的记录。\n", target_id);
        }
    } else if (q_choice == 2) {
        char target_name[50];
        printf("请输入查询姓名: "); scanf("%s", target_name);
        int found = 0;
        for (int i = 0; i < emp_count; i++) {
            if (strcmp(emps[i].name, target_name) == 0) {
                if (!found) printf("\n%-10s %-12s %-12s %-10s %-10s %-10s %-10s %-10s\n", 
                                  "编号", "姓名", "部门", "职称", "基本工资", "加班工资", "奖金", "总工资");
                printf("%-10s %-12s %-12s %-10s %-10.2f %-10.2f %-10.2f %-10.2f\n", 
                       emps[i].id, emps[i].name, emps[i].dept, emps[i].title, 
                       emps[i].base_salary, emps[i].extra_salary, emps[i].bonus, emps[i].total_salary);
                found = 1;
            }
        }
        if (!found) printf("未找到姓名为 %s 的记录。\n", target_name);
    }
}

int cmp_total(const void *a, const void *b) {
    double diff = ((Employee*)b)->total_salary - ((Employee*)a)->total_salary;
    return (diff > 0) ? 1 : (diff < 0 ? -1 : 0);
}

int cmp_base(const void *a, const void *b) {
    double diff = ((Employee*)b)->base_salary - ((Employee*)a)->base_salary;
    return (diff > 0) ? 1 : (diff < 0 ? -1 : 0);
}

void sort_employees() {
    int s_choice;
    printf("1. 按总工资降序  2. 按基本工资降序: ");
    scanf("%d", &s_choice);
    if (s_choice == 1) {
        qsort(emps, emp_count, sizeof(Employee), cmp_total);
        printf("按总工资降序排序完成！\n");
    } else if (s_choice == 2) {
        qsort(emps, emp_count, sizeof(Employee), cmp_base);
        printf("按基本工资降序排序完成！\n");
    }
    output_all();
}

void delete_employee() {
    char target_id[20];
    printf("请输入要删除的职工编号: "); scanf("%s", target_id);
    int idx = find_by_id(target_id);
    if (idx == -1) {
        printf("未找到编号为 %s 的记录。\n", target_id);
        return;
    }
    for (int i = idx; i < emp_count - 1; i++) {
        emps[i] = emps[i+1];
    }
    emp_count--;
    printf("删除成功！\n");
}

void modify_employee() {
    char target_id[20];
    printf("请输入要修改的职工编号: "); scanf("%s", target_id);
    int idx = find_by_id(target_id);
    if (idx == -1) {
        printf("未找到编号为 %s 的记录。\n", target_id);
        return;
    }
    printf("当前记录：\n%-10s %-12s %-12s %-10s %-10.2f %-10.2f %-10.2f %-10.2f\n", 
           emps[idx].id, emps[idx].name, emps[idx].dept, emps[idx].title, 
           emps[idx].base_salary, emps[idx].extra_salary, emps[idx].bonus, emps[idx].total_salary);
    
    printf("请输入新姓名: "); scanf("%s", emps[idx].name);
    printf("请输入新部门: "); scanf("%s", emps[idx].dept);
    printf("请输入新职称: "); scanf("%s", emps[idx].title);
    printf("新基本工资: "); scanf("%lf", &emps[idx].base_salary);
    printf("新加班工资: "); scanf("%lf", &emps[idx].extra_salary);
    printf("新奖金: "); scanf("%lf", &emps[idx].bonus);
    emps[idx].total_salary = calculate_total(&emps[idx]);
    printf("修改成功！\n");
}

void analyze_dept() {
    char target_dept[50];
    printf("请输入要分析的部门名称: "); scanf("%s", target_dept);
    
    double sum_salary = 0;
    int dept_count = 0;
    
    typedef struct {
        char title_name[50];
        int count;
    } TitleStat;
    TitleStat stats[MAX_EMPLOYEES];
    int title_kind_count = 0;

    for (int i = 0; i < emp_count; i++) {
        if (strcmp(emps[i].dept, target_dept) == 0) {
            sum_salary += emps[i].total_salary;
            dept_count++;
            
            // 统计职称
            int found_title = 0;
            for (int j = 0; j < title_kind_count; j++) {
                if (strcmp(stats[j].title_name, emps[i].title) == 0) {
                    stats[j].count++;
                    found_title = 1;
                    break;
                }
            }
            if (!found_title) {
                strcpy(stats[title_kind_count].title_name, emps[i].title);
                stats[title_kind_count].count = 1;
                title_kind_count++;
            }
        }
    }
    
    if (dept_count == 0) {
        printf("找不到部门为 %s 的职工记录。\n", target_dept);
        return;
    }
    
    printf("\n--- 部门 [%s] 分析报告 ---\n", target_dept);
    printf("总人数: %d\n", dept_count);
    printf("平均工资: %.2f\n", sum_salary / dept_count);
    printf("职称占比统计:\n");
    for (int i = 0; i < title_kind_count; i++) {
        printf("  %-10s: %d 人 (%.2f%%)\n", 
               stats[i].title_name, stats[i].count, 
               (stats[i].count * 100.0) / dept_count);
    }
    printf("---------------------------\n");
}
