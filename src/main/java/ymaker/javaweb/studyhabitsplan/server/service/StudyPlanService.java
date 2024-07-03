package ymaker.javaweb.studyhabitsplan.server.service;

import com.baomidou.mybatisplus.core.conditions.query.QueryWrapper;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import ymaker.javaweb.studyhabitsplan.common.Context.BaseContext;
import ymaker.javaweb.studyhabitsplan.pojo.StudyPlan;
import ymaker.javaweb.studyhabitsplan.server.mapper.StudyPlanMapper;

import java.util.Date;
import java.util.List;

@Service
public class StudyPlanService implements Study_Plan {

    @Autowired
    StudyPlanMapper studyPlanMapper;

    @Override
    public StudyPlan getStudyPlanById(int id) {
        return studyPlanMapper.selectById(id);
    }

    @Override
    public List<StudyPlan> getStudyPlans(String content,String topic,Integer priority,String username) {
        QueryWrapper<StudyPlan> queryWrapper=new QueryWrapper<>();
        if(content!=null){
            queryWrapper.like("content",content);
        }
        if(topic!=null){
            queryWrapper.like("topic",topic);
        }
        if(priority!=null){
            queryWrapper.eq("priority",priority);
        }
        queryWrapper.eq("username",username);
        return studyPlanMapper.selectList(queryWrapper);
    }

    @Override
    public List<StudyPlan> getAllStudyPlan(String username) {
        return studyPlanMapper.selectList(new QueryWrapper<StudyPlan>().eq("username",username));
    }

    @Override
    public void addStudyPlan(StudyPlan studyPlan) {
        studyPlanMapper.insert(studyPlan);
    }

    @Override
    public void deleteStudyPlan(int id) {
        studyPlanMapper.deleteById(id);
    }

    @Override
    public void updateStudyPlan(StudyPlan studyPlan) {
        studyPlanMapper.updateById(studyPlan);
    }

    @Override
    public List<StudyPlan> getStudyPlanByTime(Date startTime,Date endTime,String username) {
        QueryWrapper<StudyPlan> queryWrapper=new QueryWrapper<>();
        if(startTime!=null){
            queryWrapper.ge("deadline",startTime);
        }
        if(endTime!=null){
            queryWrapper.lt("deadline",endTime);
        }
        queryWrapper.eq("username",username);
        return studyPlanMapper.selectList(queryWrapper);
    }

    public List<StudyPlan> getStudyPlanByStatus(int status){
        String username= BaseContext.getCurrentUsername();
        QueryWrapper<StudyPlan> queryWrapper=new QueryWrapper<>();
        queryWrapper.eq("username",username).eq("status",status);
        return studyPlanMapper.selectList(queryWrapper);
    }
}
