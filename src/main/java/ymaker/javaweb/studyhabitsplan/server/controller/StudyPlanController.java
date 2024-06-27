package ymaker.javaweb.studyhabitsplan.server.controller;


import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;
import ymaker.javaweb.studyhabitsplan.common.Context.BaseContext;
import ymaker.javaweb.studyhabitsplan.common.Result.Result;
import ymaker.javaweb.studyhabitsplan.pojo.StudyPlan;
import ymaker.javaweb.studyhabitsplan.server.service.StudyPlanService;

import java.util.Date;
import java.util.List;

@RestController()
@RequestMapping("/studyPlan")
public class StudyPlanController {
    @Autowired
    StudyPlanService studyPlanService;

    @PostMapping("/add")
    public Result<StudyPlan> addStudyPlan(@RequestBody StudyPlan studyPlan){
        studyPlanService.addStudyPlan(studyPlan);
        return Result.success();
    }

    @RequestMapping("/getAll")
    public Result getAllStudyPlans(String username){
        if(null!=username){
            List<StudyPlan> allStudyPlan = studyPlanService.getAllStudyPlan(username);
            StudyPlan first = allStudyPlan.getFirst();
            System.out.println(first.getDeadline());

            return Result.success(allStudyPlan);
        }else {
            String currentUsername = BaseContext.getCurrentUsername();
            if(null==currentUsername)return Result.error("未登录");
            List<StudyPlan> allStudyPlan = studyPlanService.getAllStudyPlan(currentUsername);
            return Result.success(allStudyPlan);
        }
    }

    @RequestMapping("/delete")
    public Result deleteStudyPlan(int id){
        studyPlanService.deleteStudyPlan(id);
        return Result.success();
    }

    @PostMapping("/update")
    public Result updateStudyPlan(@RequestBody StudyPlan studyPlan){
        studyPlanService.updateStudyPlan(studyPlan);
        return Result.success();
    }

    @PostMapping("/get")
    public Result getStudyPlan(String content,String topic,Integer priority,String username){
        if(null!=username){
            List<StudyPlan> studyPlans = studyPlanService.getStudyPlans(content, topic, priority, username);
            return Result.success(studyPlans);
        }
        else {
            String currentUsername = BaseContext.getCurrentUsername();
            if(null==currentUsername)return Result.error("未登录");
            List<StudyPlan> studyPlans = studyPlanService.getStudyPlans(content, topic, priority, currentUsername);
            return Result.success(studyPlans);
        }
    }

    @PostMapping("/getByTime")
    public Result getStudyPlanByTime(Date startTime,Date endTime,String username){
        if(null!=username){
            List<StudyPlan> studyPlans = studyPlanService.getStudyPlanByTime(startTime,endTime,username);
            return Result.success(studyPlans);
        }
        else {
            String currentUsername = BaseContext.getCurrentUsername();
            if(null==currentUsername)return Result.error("未登录");
            List<StudyPlan> studyPlans = studyPlanService.getStudyPlanByTime(startTime,endTime,currentUsername);
            return Result.success(studyPlans);
        }
    }


}
