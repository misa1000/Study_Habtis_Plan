package ymaker.javaweb.studyhabitsplan.server.conf;


import jakarta.servlet.http.PushBuilder;
import org.springframework.web.bind.annotation.ControllerAdvice;
import org.springframework.web.bind.annotation.ExceptionHandler;
import org.springframework.web.bind.annotation.ResponseBody;
import ymaker.javaweb.studyhabitsplan.common.Result.Result;

@ControllerAdvice
public class MyExceptionHandler {

    @ResponseBody
    @ExceptionHandler(Exception.class)
    public Result exceptionHandler(Exception e){
        return Result.error("出错了");
    }

}
