package com.andressasmedeiros.horta.controller;

import com.andressasmedeiros.horta.model.Status;
import com.andressasmedeiros.horta.service.StatusService;
import org.springframework.web.bind.annotation.*;

@RestController
@RequestMapping("/api")
public class StatusController {

    private final StatusService service;

    public StatusController(StatusService service) {
        this.service = service;
    }

    // Endpoint GET - Retorna o último status salvo
    @GetMapping("/status")
    public Status getStatus() {
        return service.getStatus();
    }

    // Endpoint POST - Recebe dados do ESP32 e retorna confirmação
    @PostMapping("/status")
    public Status atualizarStatus(@RequestBody Status novoStatus) {
        // Salva o novo status
        service.setStatus(novoStatus);

        // Retorna os dados para confirmação
        return novoStatus;
    }
}
