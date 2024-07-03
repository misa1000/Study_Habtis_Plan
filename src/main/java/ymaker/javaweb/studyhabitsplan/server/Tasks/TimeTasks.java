package ymaker.javaweb.studyhabitsplan.server.Tasks;

import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.scheduling.annotation.Scheduled;
import org.springframework.stereotype.Component;
import ymaker.javaweb.studyhabitsplan.common.Context.BaseContext;
import ymaker.javaweb.studyhabitsplan.pojo.StudyPlan;
import ymaker.javaweb.studyhabitsplan.server.WebSocket.WebSocketServer;
import ymaker.javaweb.studyhabitsplan.server.service.StudyPlanService;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.List;

@Component
@Slf4j
public class TimeTasks {
    @Autowired
    StudyPlanService studyPlanMapperService;
    @Autowired
    WebSocketServer webSocketServer;

    @Scheduled(cron = "0 * * * * *")//设置为每分钟触发一次
    public void remindtask() {
        String currentUsername = BaseContext.getCurrentUsername();
        Date now = new Date();
        List<StudyPlan> studyPlanByTime = studyPlanMapperService.getStudyPlanByTime(null, now, currentUsername);
        for (StudyPlan studyPlan : studyPlanByTime) {

            long l = now.getTime() - studyPlan.getDeadline().getTime();//获取到截止时间与当前时间的差值
            switch ((int) l/1000/60){
                case 30:
                    webSocketServer.sendToAllClient("30m"+studyPlan.getTopic()+"需要复习");
                    break;
                case 60:
                    webSocketServer.sendToAllClient("1h"+studyPlan.getTopic()+"需要复习");
                    break;
                case 480:
                    webSocketServer.sendToAllClient("8h"+studyPlan.getTopic()+"需要复习");
                    break;
                case 1440:
                    webSocketServer.sendToAllClient("1day"+studyPlan.getTopic()+"需要复习");
                    break;
                case 10080:
                    webSocketServer.sendToAllClient("1week"+studyPlan.getTopic()+"需要复习");
                    break;
            }
        }
    }

    @Scheduled(cron = "0 * * * * *")
    public void reminder(){
        String currentUsername = BaseContext.getCurrentUsername();
        Date date=new Date();
        SimpleDateFormat simpleDateFormat=new SimpleDateFormat("yyyy-MM-dd HH:mm");
        String current = simpleDateFormat.format(date);
        List<StudyPlan> studyPlanByTime = studyPlanMapperService.getStudyPlanByTime(date, null, currentUsername);

        for (StudyPlan studyPlan:studyPlanByTime) {
            String[] split = studyPlan.getReminder_time().split("//");
            for (String s:split) {
                if(current.equals(s)) {
                    webSocketServer.sendToAllClient(studyPlan.getTopic()+"需要复习");
                }
            }

        }


    }


}