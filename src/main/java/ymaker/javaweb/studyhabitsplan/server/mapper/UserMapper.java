package ymaker.javaweb.studyhabitsplan.server.mapper;

import org.apache.ibatis.annotations.Insert;
import org.apache.ibatis.annotations.Mapper;
import ymaker.javaweb.studyhabitsplan.pojo.User;

@Mapper
public interface UserMapper {
    @Insert("insert into user (username,password) values (#{username},#{password})")
    public void insert(String username, String password);
}
