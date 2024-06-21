package ymaker.javaweb.studyhabitsplan.server.controller;

import io.swagger.annotations.Api;
import lombok.extern.slf4j.Slf4j;
import org.springframework.web.bind.annotation.*;
import ymaker.javaweb.studyhabitsplan.common.Result.Result;

@RestController
@RequestMapping("/studytasks")
@Slf4j
@Api(tags = "学习任务模块有关接口")
public class Study_Tasks {
    @PostMapping("/insert")
    public Result insert() {
        return Result.success("OK");
    }

    @PutMapping("/delete")
    public Result delete() {
        return Result.success();
    }

    @GetMapping("/select")
    public Result select() {
        return Result.success();
    }
}

