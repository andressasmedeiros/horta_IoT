package com.andressasmedeiros.horta.service;

import com.andressasmedeiros.horta.model.Status;
import org.springframework.stereotype.Service;

@Service
public class StatusService {

    // Armazena o último status recebido do Arduino
    private Status statusAtual = new Status();

    public Status getStatus() {
        // Calcula statusAgua dinamicamente com base na umidade do solo
        if (statusAtual.getUmidadeSolo() < 30) {
            statusAtual.setStatusAgua(0); // 0 = Precisa regar
        } else if (statusAtual.getUmidadeSolo() <= 70) {
            statusAtual.setStatusAgua(1); // 1 = Água média
        } else {
            statusAtual.setStatusAgua(2); // 2 = Solo encharcado / Não precisa regar
        }

        return statusAtual;
    }

    // Atualiza o status atual com novos dados do Arduino
    public void setStatus(Status novoStatus) {
        if (novoStatus != null) {
            this.statusAtual = novoStatus;
        }
    }
}
