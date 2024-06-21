package ymaker.javaweb.studyhabitsplan.pojo;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@AllArgsConstructor
@NoArgsConstructor
public class UserLogin {
    private String username;
    private String token;
}
//该类被用来向前端返回一个jwttoken

