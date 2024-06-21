package ymaker.javaweb.studyhabitsplan.server.controller;

import io.swagger.annotations.Api;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;
import ymaker.javaweb.studyhabitsplan.common.Result.Result;
import ymaker.javaweb.studyhabitsplan.server.service.Userservice;

@RestController
@RequestMapping("/user")
@Slf4j
@Api(tags = "学习任务模块有关接口")
public class User_Controllers {
    @Autowired
    public Userservice userservice;
    @PostMapping("/register")
    public Result register(String username, String password) {
            userservice.register(username,password);
            return Result.success();
        }
    }
