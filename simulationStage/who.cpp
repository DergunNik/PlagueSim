#include "who.h"

WHO::WHO(QObject *parent)
    : QObject{parent}
{}


WHO::WHO(Statistics *stat, QVector<Citizen> *citizens, QObject *parent) :
    QObject{parent},
    _stat(stat),
    _citizens(citizens)
{}


void WHO::checkState()
{
    auto state = _stat->history().back();
    float percent = static_cast<float>(state.haveSymptoms) / state.alive;
    if (percent > REC_LEVEL && !_hands) {
        _hands = true;
        emit news(QString("В связи с распространением нового заболевания врачи просят граждан "
                          "тщательно мыть руки и избегать людей, проявляющих признаки простуты."));
    }
    if (percent > MASKS_LEVEL && !_masks) {
        provideMasks();
    }
    if (percent > MIN_CONT_LEVEL && !_minimalContacts) {
        provideMinimalContacts();
    }
    if (percent > VACCINE_LEVEL && !_vaccination) {
        provideVaccination();
    }
    if (percent > ISOLATION_LEVEL && !_selfIsolation) {
        provideSelfIsolation();
    }
    if (percent > HALF_LEVEL && !_halfIsInf) {
        _halfIsInf = true;
        emit news(QString("Каждый второй в городе болен! \"Я здоров - а Вы?\" - спрашивают врачи."));
    }
    if (qAbs(1 - percent) <= ONE_PRECISION && !_everyIsInf) {
        _everyIsInf = true;
        emit news(QString("\"Болеют ВСЕ!\" - заявляют врачи."));
    }
}


void WHO::provideMasks()
{
    _masks = true;

    for (auto& now : *_citizens) {
        if (now.responsibility() == RESPONSIBLE) {
            now.setIsWearingMask(true);
        }
    }

    emit news(QString("Врачи указывают на растущие цифры заражённых новой болезнью,"
                      " они рекомендуют носить медицинские маски, независимо от вашего самочуствия."));
}


void WHO::provideMinimalContacts()
{
    _minimalContacts = true;

    for (auto& now : *_citizens) {
        if (now.responsibility() == RESPONSIBLE) {
            now.setSociability(now.sociability() / 2);
        }
    }

    emit news(QString("Врачи заявляют, что новой болезнью заражён каждый десятый житель города."
                      "Они настоятельно рекомендуют воздержаться от любых личных контактов или свести их к минимуму."));
}


void WHO::provideVaccination()
{
    _vaccination = true;

    for (auto& now : *_citizens) {
        if (now.responsibility() == RESPONSIBLE && !now.isVaccinated()) {
            now.getVaccinated();
        }
    }

    emit news(QString("\"20% города жалуется на симптомы новой болезни,\" - заявляют медики. "
                      "В связи с этим они призывают всех невакцинированных людей срочно это исправлять, "
                      "чтобы обезопасить свою жизнь и жизни близких."));
}


void WHO::provideSelfIsolation()
{
    _selfIsolation = true;

    for (auto& now : *_citizens) {
        if (now.responsibility() == RESPONSIBLE) {
            now.setIsOnSelfIsolation(true);
        }
    }

    emit news(QString("Как минимум каждый третий житель города заражён новой болезнью! "
                      "Врачи призывают население к немедлонной самоизоляции."));
}
