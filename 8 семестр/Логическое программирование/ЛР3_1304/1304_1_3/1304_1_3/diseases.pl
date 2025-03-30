% Файл: diseases.pl
% База знаний для экспертной системы "Электронный терапевт"
% Каждая запись имеет вид: disease(Заболевание, [Симптом1, Симптом2, ...]).
% Для многословных названий симптомов используется символ подчёркивания.

disease('gripp', ['kashel', 'vysokaya_temperatura', 'golovnaya_bol', 'lomota_v_myshcakh', 'ustalost']).
disease('prostuda', ['nasmork', 'chikhaniye', 'legkaya_temperatura']).
disease('angina', ['bol_v_gorle', 'zatrudnennoye_glotanie', 'vysokaya_temperatura']).
disease('allergiya', ['chikhaniye', 'zud', 'slezotecheniye', 'nasmork']).
disease('pnevmoniya', ['silnyy_kashel', 'vysokaya_temperatura', 'odyshka', 'bol_v_grudi']).
disease('bronhit', ['kashel', 'vydeleniya_iz_legkikh', 'ustalost', 'nebolshaya_temperatura']).
disease('pishchevoye_otravleniye', ['toshnota', 'rvota', 'bol_v_zhivote', 'diareya']).
disease('migreny', ['silnaya_golovnaya_bol', 'toshnota', 'svetoboyazn']).
disease('diabet', ['zhazhda', 'chastoye_mocheispuskaniye', 'ustalost', 'povyshennyy_sakhar']).
disease('gipertonya', ['golovnaya_bol', 'golovokruzheniye', 'shum_v_usakh']).
disease('ostraya_angina', ['bol_v_gorle', 'likhoradka', 'vysokaya_temperatura']).
disease('sinusit', ['zalozhennost_nosa', 'golovnaya_bol', 'bol_v_litse']).
disease('tonzillit', ['bol_v_gorle', 'uvelichenie_limfaticheskikh_uzlov', 'vysokaya_temperatura']).
disease('meningit', ['silnaya_golovnaya_bol', 'rigidnost_shei', 'vysokaya_temperatura', 'toshnota']).
disease('uretrit', ['boleznennoye_mocheispuskaniye', 'vydeleniya', 'zhzheniye']).
disease('tsistit', ['boleznennoye_mocheispuskaniye', 'chastye_pozyvy_k_mocheispuskaniyu', 'bol_v_zhivote']).
disease('artrit', ['bol_v_sustavakh', 'otek', 'skovannost']).
disease('revmatizm', ['bol_v_sustavakh', 'ustalost', 'likhoradka', 'slabost']).
disease('gepatit', ['zheltyuka', 'bol_v_zhivote', 'ustalost', 'poterya_appetita']).
disease('infektsiya_pishchevaritelnogo_trakta', ['bol_v_zhivote', 'diareya', 'rvota', 'toshnota']).
disease('koronavirus', ['kashel', 'vysokaya_temperatura', 'odyshka', 'poterya_obonyaniya', 'utomlyaemost']).
disease('otit', ['bol_v_uhe', 'snizheniye_slukha', 'likhoradka']).
disease('zheludochnaya_yazva', ['bol_v_zhivote', 'izzhoga', 'toshnota', 'rvota']).
disease('pankreatit', ['bol_v_zhivote', 'toshnota', 'rvota', 'likhoradka']).
disease('epilepsiya', ['pristupy', 'poterya_soznaniya', 'sudorogi']).
disease('insult', ['vnezapnaya_slabost', 'zatrudnennaya_rech', 'poterya_koordinatsii', 'golovnaya_bol']).