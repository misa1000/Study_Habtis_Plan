package ymaker.javaweb.studyhabitsplan.pojo;


import com.baomidou.mybatisplus.annotation.FieldFill;
import com.baomidou.mybatisplus.annotation.TableField;
import com.baomidou.mybatisplus.annotation.TableName;
import com.fasterxml.jackson.annotation.JsonFormat;
import lombok.Data;

import java.time.LocalDateTime;
import java.util.Date;

@Data
@TableName("`study-plans`")
public class StudyPlan {
    private int id;
    private String username;
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss")
    private Date deadline;
    private String topic;
    private int priority;
    private String content;
    @TableField(value = "create_time",fill = FieldFill.INSERT)
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss")
    private Date createTime;
    @TableField(value = "update_time",fill = FieldFill.UPDATE)
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss")
    private Date updateTime;
    private int status;
    private String reminder_time;
    //"yyyy-MM-dd HH:mm//yyyy-MM-dd HH:mm"
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss")
    private Date finish_time;

}
