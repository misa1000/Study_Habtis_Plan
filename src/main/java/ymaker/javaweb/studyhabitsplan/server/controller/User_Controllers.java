package ymaker.javaweb.studyhabitsplan.server.controller;

import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;
import ymaker.javaweb.studyhabitsplan.common.Result.Result;
import ymaker.javaweb.studyhabitsplan.common.utils.JwtUtil;
import ymaker.javaweb.studyhabitsplan.pojo.User;
import ymaker.javaweb.studyhabitsplan.pojo.UserLogin;
import ymaker.javaweb.studyhabitsplan.server.service.Userservice;

import java.util.HashMap;
import java.util.Map;

@RestController
@RequestMapping("/user")
@Slf4j
@Api(tags = "学习任务模块有关接口")
public class User_Controllers {
    @Autowired
    public Userservice userservice;
    @PostMapping("/register")
    @ApiOperation("用户注册")
    public Result register(String username, String password) {
            userservice.register(username,password);
            return Result.success();
        }
        @PostMapping("/login")
        @ApiOperation("用户登陆")
        public Result<UserLogin> login(@RequestBody User user) {
            log.info("员工登录：{}",user);
            User a =userservice.login(user);

            //登录成功后，生成jwt令牌
                Map<String, Object> claims = new HashMap<>();
                claims.put("userid",a.getId());
                String token = JwtUtil.createJWT(
                        "Misaka",
                        3600000L,
                        claims);
log.info(token);
                UserLogin userLogin = new UserLogin();
                userLogin.setToken(token);
                userLogin.setUsername(a.getUsername());
                return Result.success(userLogin);
            }
    }
