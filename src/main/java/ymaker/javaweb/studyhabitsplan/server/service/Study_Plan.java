package ymaker.javaweb.studyhabitsplan.server.service;

import ymaker.javaweb.studyhabitsplan.pojo.StudyPlan;

import java.util.Date;
import java.util.List;

public interface Study_Plan {
    public StudyPlan getStudyPlanById(int id);

    public List<StudyPlan> getStudyPlans(String content,String topic,Integer priority,String username);

    public List<StudyPlan> getAllStudyPlan(String username);

    public void addStudyPlan(StudyPlan studyPlan);
    public void deleteStudyPlan(int id);

    public void updateStudyPlan(StudyPlan studyPlan);

    public List<StudyPlan> getStudyPlanByTime(Date startTime,Date endTime,String username);

}
