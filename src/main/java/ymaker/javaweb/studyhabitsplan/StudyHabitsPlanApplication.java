package ymaker.javaweb.studyhabitsplan;

import org.mybatis.spring.annotation.MapperScan;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.scheduling.annotation.EnableScheduling;
import org.springframework.scheduling.annotation.Scheduled;
import springfox.documentation.swagger2.annotations.EnableSwagger2;
@EnableScheduling//允许定时任务调度的开启
@SpringBootApplication
@MapperScan("ymaker.javaweb.studyhabitsplan.server.mapper")
public class StudyHabitsPlanApplication {

	public static void main(String[] args) {
		SpringApplication.run(StudyHabitsPlanApplication.class, args);
	}

}
