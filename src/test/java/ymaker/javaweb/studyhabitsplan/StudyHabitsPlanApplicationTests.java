package ymaker.javaweb.studyhabitsplan;

import org.junit.jupiter.api.Test;
import org.springframework.boot.test.context.SpringBootTest;

@SpringBootTest
class StudyHabitsPlanApplicationTests {

	@Test
	void contextLoads() {
		long l = now.getTime() - studyPlan.getDeadline().getTime();
	}

}
