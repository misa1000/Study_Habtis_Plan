package ymaker.javaweb.studyhabitsplan.common.utils;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;
import ymaker.javaweb.studyhabitsplan.common.Context.BaseContext;
import ymaker.javaweb.studyhabitsplan.pojo.StudyPlan;
import ymaker.javaweb.studyhabitsplan.server.service.StudyPlanService;

import java.util.*;

@Component
//系统推荐算法设计————根据学习计划本身的属性（优先级和截止时间）
public class RecommendAlgorithm {
    @Autowired
    StudyPlanService studyPlanService;
    public List<StudyPlan> recommend() {
        String currentUsername = BaseContext.getCurrentUsername();
        List<StudyPlan> allStudyPlan = studyPlanService.getAllStudyPlan(currentUsername);
        List<StudyPlan> oneWeekStudyPlan=new ArrayList<StudyPlan>();//during one week
        List<StudyPlan> outOneWeekStudyPlan=new ArrayList<StudyPlan>();// over one week
        List<StudyPlan> SortedStudyPlan=new ArrayList<StudyPlan>();//设置一个ArrayList用来存放排序以后的计划表
        Map<StudyPlan, Integer> studyPlanMap=new HashMap<StudyPlan, Integer>();//建立一个映射方便后续排序使用
        //首先对这个计划表进行分类
        for (StudyPlan studyPlan : allStudyPlan) {

            Date now = new Date();
        //如果距离截止时间的时间大于一周，直接按照优先级排序
            if(studyPlan.getDeadline().getTime()-now.getTime()>7*24*60*60*1000) {
                    outOneWeekStudyPlan.add(studyPlan);
            }else {
                oneWeekStudyPlan.add(studyPlan);
            }
            //完成了一级分类
           }

        //接下来先对截止时间小于一周的部分进行排序（权重计算）
        for (StudyPlan plan : oneWeekStudyPlan) {
            int priority_weight = 0;//优先级权重
            int time_weight=0;//时间权重
            int priority = plan.getPriority();//获取优先级
            Date deadline = plan.getDeadline();//获取该计划的截止时间
            Date now = new Date();//获取当前的时间
            switch (priority) {
                case 1:
                    priority_weight = 4;
                    break;
                    case 2:
                        priority_weight = 3;
                        break;
                        case 3:
                            priority_weight = 2;
                            break;
                            case 4:
                                priority_weight = 1;
                                break;
            }
            //接下来计算时间的权重
            Long time=deadline.getTime()-now.getTime();
            int times=time.intValue()/1000;
            if(times<=7*24*60*60&&times>3*24*60*60) {
                time_weight=1;
            }//3day-7day
            else if(times<=3*24*60*60&&times>24*60*60){
                time_weight=2;
       }//1day-3day
            else  if(times<=24*60*60&&times>8*60){
                time_weight=3;
            }//8h-1day
            else{
                    time_weight=4;
            }//8h以内
            //计算总的权重积
                    int push_score = priority_weight * time_weight;
                    studyPlanMap.put(plan,push_score);


        }

        oneWeekStudyPlan.sort(new Comparator<StudyPlan>() {
            @Override
            public int compare(StudyPlan studyPlan, StudyPlan t1) {
                return studyPlanMap.get(studyPlan)-studyPlanMap.get(t1);
            }
        });//根据权重进行排序
        SortedStudyPlan.addAll(oneWeekStudyPlan);//加入到最终list中

        //然后是对超过一周时间的计划进行权重计算（实际只根据优先级进行排序即可）
        outOneWeekStudyPlan.sort(new Comparator<StudyPlan>() {
            @Override
            public int compare(StudyPlan s1, StudyPlan s2) {
                return s1.getPriority()-s2.getPriority();
            }
        });
        //添加到最终list里面
        SortedStudyPlan.addAll(outOneWeekStudyPlan);
        //返回最终list
        return SortedStudyPlan;
    }
    }
