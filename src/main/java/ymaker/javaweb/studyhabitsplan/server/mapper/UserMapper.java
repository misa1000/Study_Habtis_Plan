package ymaker.javaweb.studyhabitsplan.server.mapper;

import org.apache.ibatis.annotations.Insert;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Select;
import ymaker.javaweb.studyhabitsplan.pojo.User;

@Mapper
public interface UserMapper {
    /**
     * 用户注册
     * @param username
     * @param password
     */
    @Insert("insert into user (username,password) values (#{username},#{password})")
    public void insert(String username, String password);

    @Select("select * from user where username=#{username} and password=#{password}")
    public User login(User user);
}
