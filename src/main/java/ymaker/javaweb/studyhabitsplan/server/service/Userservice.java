package ymaker.javaweb.studyhabitsplan.server.service;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.util.DigestUtils;
import ymaker.javaweb.studyhabitsplan.common.Context.BaseContext;
import ymaker.javaweb.studyhabitsplan.pojo.User;
import ymaker.javaweb.studyhabitsplan.server.mapper.UserMapper;

@Service
public class Userservice implements UserServiceInter{
    @Autowired
    public UserMapper userMapper;
    @Override
    public void register(String username, String password) {
        //对密码进行md5哈希算法转化以后再存储到数据库里面
        String s = DigestUtils.md5DigestAsHex(password.getBytes());
        userMapper.insert(username,s);
    }

    public User login(User user) {
        user.setPassword(DigestUtils.md5DigestAsHex(user.getPassword().getBytes()));
        User q = userMapper.login(user);
        if(q !=null){
            BaseContext.setCurrentUsername(q.getUsername());
        }
        return q;
    }
}
