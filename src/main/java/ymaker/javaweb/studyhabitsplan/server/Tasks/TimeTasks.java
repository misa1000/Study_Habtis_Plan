package ymaker.javaweb.studyhabitsplan.server.Tasks;

import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.scheduling.annotation.Scheduled;
import org.springframework.stereotype.Component;
import ymaker.javaweb.studyhabitsplan.common.Context.BaseContext;
import ymaker.javaweb.studyhabitsplan.server.mapper.StudyPlanMapper;
import ymaker.javaweb.studyhabitsplan.server.service.StudyPlanService;

import java.time.LocalDateTime;

@Component
@Slf4j
public class TimeTasks {
    @Autowired
    StudyPlanService studyPlanMapperService;

    @Scheduled(cron = "0 * * * * *")//设置为每分钟触发一次
    public void timeTask() {
        Long userId = BaseContext.getCurrentId();
        LocalDateTime now = LocalDateTime.now();
        studyPlanMapperService.getStudyPlanByTime()
    }
}