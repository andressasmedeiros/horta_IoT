package com.andressasmedeiros.horta.config;

import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.web.servlet.config.annotation.CorsRegistry;
import org.springframework.web.servlet.config.annotation.WebMvcConfigurer;

@Configuration
public class WebConfig {

    @Bean
    public WebMvcConfigurer corsConfigurer() {
        return new WebMvcConfigurer() {
            @Override
            public void addCorsMappings(CorsRegistry registry) {
                registry.addMapping("/api/**")
                        .allowedOrigins("*") // Pode mudar futuramente para o IP do ESP32 ou do Front
                        .allowedMethods("GET", "POST")
                        .allowedHeaders("*")
                        .allowCredentials(false);
            }
        };
    }
}
